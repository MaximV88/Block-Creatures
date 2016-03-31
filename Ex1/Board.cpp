//
//  Board.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Board.hpp"
#include "Rule.hpp"
#include "ClassicRule.hpp"

#include "Tile.hpp"
#include "FlatBoard.hpp"
#include "CircularBoard.hpp"
#include "Window.hpp"
#include <iostream>

class Board::Impl {
public:
    
    Impl(Board&);
    ~Impl();
    
    virtual Block GetBlock(const Tile& marker) const;
    
    void AddRule(Rule* rule);
    void AddClassicRule(ClassicRule* rule);

    void ClearRules();
    void Simulate();
    void Resize(const Sizable& size);
    void Toggle(int pos_x, int pos_y);
    void Reset();
    
    void Draw(WINDOW* win) const;
    
    Tile* GetTile(int pos_x, int pos_y) const;

private:
    
    typedef std::pair<Tile**, Tile**> board_t;
    
    int Index(int pos_x, int pos_y) const;
    board_t InitializeBoard(int width, int height) const;
    
    void SimulateRules();
    void SimulateClassicRules();
    
    Direction LocalPositionInBlock(const Tile& marker) const;
    Direction LocalPositionInBlockByRed(const Tile& marker) const;
    Direction LocalPositionInBlockByBlue(const Tile& marker) const;
    
    void DeallocateBoard(Tile** board, int width, int height) const;
    
    board_t m_board;
    int m_generation;
    std::vector<Rule*> m_rules;
    std::vector<ClassicRule*> m_classic_rules;
    
    Board& m_owner;
    
};

#pragma mark - Implementation

Board::Impl::Impl(Board& owner) :
m_owner(owner),
m_generation(0) {
    
    bool initialized = false;
    while (!initialized) {
        
        try {
            
            //Allocate heap memory
            m_board = InitializeBoard(m_owner.GetWidth(), m_owner.GetHeight());
            
            initialized = true;
            
        } catch (...) {
            
            //Retry
            initialized = false;
            
        }
    }
}

Board::Impl::~Impl() {
    
    DeallocateBoard(m_board.first, m_owner.GetWidth(), m_owner.GetHeight());
    DeallocateBoard(m_board.second, m_owner.GetWidth(), m_owner.GetHeight());
    
    //Delete all rules
    for (std::vector<Rule*>::iterator start = m_rules.begin(), end = m_rules.end() ;
         start != end ;
         start++)
        delete *start;
    
}

void Board::Impl::Resize(const Sizable& size) {
    
    DeallocateBoard(m_board.first, size.GetWidth(), size.GetHeight());
    DeallocateBoard(m_board.second, size.GetWidth(), size.GetHeight());
    
    bool initialized = false;
    while (!initialized) {
        
        try {
            
            //Allocate heap memory
            m_board = InitializeBoard(m_owner.GetWidth(), m_owner.GetHeight());
            
            initialized = true;
            
        } catch (...) {
            
            //Retry
            initialized = false;
            
        }
    }
}

void Board::Impl::AddRule(Rule *rule) {
    
    //Not using smart pointers due to older version of C++
    m_rules.push_back(rule);
    
}

void Board::Impl::AddClassicRule(ClassicRule *rule) {
    m_classic_rules.push_back(rule);
}

void Board::Impl::ClearRules() {
    
    for (std::vector<Rule*>::iterator begin = m_rules.begin(), end = m_rules.end() ;
         begin != end ;
         begin++) {
        
        //Remove all the rules
        delete (*begin);
        
    }
    
    m_rules.clear();
    
    for (std::vector<ClassicRule*>::iterator begin = m_classic_rules.begin(), end = m_classic_rules.end() ;
         begin != end ;
         begin++) {
        
        //Remove all the rules
        delete (*begin);
        
    }
    
    m_classic_rules.clear();
}

void Board::Impl::SimulateRules() {
    
    int owner_width = m_owner.GetWidth();
    int owner_height = m_owner.GetHeight();
    
    /*
     * Since the blocks are at size 2x2 to
     * avoid triggering each block twice iterate
     * at jumps of 2.
     */
    for (int width = 0 ; width < owner_width ; width += 2) {
        for (int height = 0 ; height < owner_height ; height += 2) {
            
            Block block = GetBlock(*GetTile(width, height));
            
            //Check if valid
            if (block.top_left &&
                block.top_right &&
                block.bottom_left &&
                block.bottom_right) {
                
                //Apply each rule for every block
                for (std::vector<Rule*>::iterator start = m_rules.begin(), end = m_rules.end() ;
                     start != end ;
                     start++) {
                    
                    //Values are applied on the parallel tiles
                    if ((*start)->Apply(block))
                        break;
                    
                }
            }
        }
    }
}

void Board::Impl::SimulateClassicRules() {
    
    int owner_width = m_owner.GetWidth();
    int owner_height = m_owner.GetHeight();
    
    for (int width = 0 ; width < owner_width ; width++) {
        for (int height = 0 ; height < owner_height ; height++) {
            
            Tile& current = *GetTile(width, height);
            
            //Apply each classic rule for every tile
            for (std::vector<ClassicRule*>::iterator start = m_classic_rules.begin(), end = m_classic_rules.end() ;
                 start != end ;
                 start++) {
                
                //Values are applied on the parallel tiles
                if ((*start)->Apply(current))
                    break;
                
            }
        }
    }
}

void Board::Impl::Simulate() {
    
    int owner_width = m_owner.GetWidth();
    int owner_height = m_owner.GetHeight();
    
    //Increment generation index to know which lines to follow
    ++m_generation;
    
    SimulateClassicRules();
    SimulateRules();
    
    //Apply all changes on the parallel tiles onto the current ones
    for (int pos_x = 0 ; pos_x < owner_width ; pos_x++)
        for (int pos_y = 0 ; pos_y < owner_height ; pos_y++)
            m_board.first[Index(pos_x, pos_y)]->m_state = m_board.second[Index(pos_x, pos_y)]->m_state;

}

Board::Block Board::Impl::GetBlock(const Tile &marker) const {
    
    Block result = { NULL, NULL, NULL, NULL };
    
    switch (LocalPositionInBlock(marker)) {
        case kTopLeft: {
        
            result.top_left = GetTile(marker.pos_x, marker.pos_y);
            result.top_right = m_owner.GetNeighbor(marker, kRight);
            result.bottom_left = m_owner.GetNeighbor(marker, kBottom);
            result.bottom_right = m_owner.GetNeighbor(marker, kBottomRight);
            
            break;
        }
        case kTopRight: {
            
            result.top_left = m_owner.GetNeighbor(marker, kLeft);
            result.top_right = GetTile(marker.pos_x, marker.pos_y);
            result.bottom_left = m_owner.GetNeighbor(marker, kBottomLeft);
            result.bottom_right = m_owner.GetNeighbor(marker, kBottom);
            
            break;
        }
        case kBottomLeft: {
            
            result.top_left = m_owner.GetNeighbor(marker, kTop);
            result.top_right = m_owner.GetNeighbor(marker, kTopRight);
            result.bottom_left = GetTile(marker.pos_x, marker.pos_y);
            result.bottom_right = m_owner.GetNeighbor(marker, kRight);
            
            break;
        }
        case kBottomRight: {
            
            result.top_left = m_owner.GetNeighbor(marker, kTopLeft);
            result.top_right = m_owner.GetNeighbor(marker, kTop);
            result.bottom_left = m_owner.GetNeighbor(marker, kLeft);
            result.bottom_right = GetTile(marker.pos_x, marker.pos_y);
            
            break;
        }
        //All fields should stay null
        default: break;
    }
    
    return result;
}

Tile* Board::Impl::GetTile(int pos_x, int pos_y) const {
    
    //Check valid position
    if (pos_x >= m_owner.GetWidth() ||
        pos_y >= m_owner.GetHeight())
        return NULL;
    
    return m_board.first[Index(pos_x, pos_y)];
}

int Board::Impl::Index(int pos_x, int pos_y) const {
    
    /*
     * The 2 dimentional array is treated as a 
     * one dimentional array to avoid having an
     * array of arrays.
     */
    return pos_x + m_owner.GetWidth() * pos_y;
}

Board::Impl::board_t Board::Impl::InitializeBoard(int width, int height) const {
    
    //The board consists of heap allocated tiles
    Tile** board_first = new Tile*[width * height];
    Tile** board_second = new Tile*[width * height];
    
    //Each tile needs to be initialized
    for (int pos_x = 0 ; pos_x < width ; pos_x++) {
        for (int pos_y = 0 ; pos_y < height ; pos_y++) {
            
            Tile* current = new Tile(pos_x, pos_y, &m_owner);
            Tile* parallel = new Tile(pos_x, pos_y, &m_owner);
            
            //Create links for each other
            current->m_parallel = parallel;
            parallel->m_parallel = current;
            
            board_first[Index(pos_x, pos_y)] = current;
            board_second[Index(pos_x, pos_y)] = parallel;
            
        }
    }
    
    return Board::Impl::board_t(board_first, board_second);
}

void Board::Impl::DeallocateBoard(Tile **board, int width, int height) const {
    
    //Remove heap allocated memory
    if (board) {
        
        for (int index = 0 ; index < height * width ; index++)
            delete board[index];
        
        delete [] board;
    }
}

Board::Direction Board::Impl::LocalPositionInBlockByRed(const Tile& marker) const {
 
    /*
     * The red lines make shape of:
     *
     *  (1,1) - (2,1)          (3,1) - (4,1)
     *    |       |      OR      |       |
     *  (1,2) - (2,2)          (3,2) - (4,2)
     *
     */
    
    if (marker.pos_x % 2 == 0) {
        
        /*
         * An even X position means that the marker is
         * at the right side of the block.
         */
        
        if (marker.pos_y % 2 == 0) {
            
            /*
             * An even Y position means that the marker is
             * at the bottom part of the block.
             */
            return Board::Direction::kBottomRight;
        }
        else {
            
            /*
             * An odd Y position means that the marker is
             * at the top part of the block.
             */
            return Board::Direction::kTopRight;
        }
    }
    else {
        
        /*
         * An odd X position means that the marker is
         * at the left side of the block.
         */
        
        if (marker.pos_y % 2 == 0) {
            
            /*
             * An even Y position means that the marker is
             * at the bottom part of the block.
             */
            return Board::Direction::kBottomLeft;
        }
        else {
            
            /*
             * An odd Y position means that the marker is
             * at the top part of the block.
             */
            return Board::Direction::kTopLeft;
        }
    }
}

Board::Direction Board::Impl::LocalPositionInBlockByBlue(const Tile& marker) const {
    
    /*
     * The blue lines make shape of:
     *
     *  (0,0) - (1,0)          (2,0) - (3,0)
     *    |       |      OR      |       |
     *  (0,1) - (1,1)          (2,1) - (3,1)
     *
     */
    
    if (marker.pos_x % 2 == 0) {
        
        /*
         * An even X position means that the marker is
         * at the left side of the block.
         */
        
        if (marker.pos_y % 2 == 0) {
            
            /*
             * An even Y position means that the marker is
             * at the top part of the block.
             */
            return Board::Direction::kTopLeft;
        }
        else {
            
            /*
             * An odd Y position means that the marker is
             * at the bottom part of the block.
             */
            return Board::Direction::kBottomLeft;
        }
    }
    else {
        
        /*
         * An odd X position means that the marker is
         * at the right side of the block.
         */
        
        if (marker.pos_y % 2 == 0) {
            
            /*
             * An even Y position means that the marker is
             * at the top part of the block.
             */
            return Board::Direction::kTopRight;
        }
        else {
            
            /*
             * An odd Y position means that the marker is
             * at the bottom part of the block.
             */
            return Board::Direction::kBottomRight;
        }
    }
}

Board::Direction Board::Impl::LocalPositionInBlock(const Tile& marker) const {
    
    //Assign tiles according to generation number
    return (m_generation % 2 == 0)
    ? LocalPositionInBlockByRed(marker)
    : LocalPositionInBlockByBlue(marker);
}

void Board::Impl::Draw(WINDOW *win) const {
    
    int owner_width = m_owner.GetWidth();
    int owner_height = m_owner.GetHeight();
    
    Window::Color prev = Window::Color::kNone;
    wattron(win, A_STANDOUT);

    //Draw all the tiles
    for (int pos_x = 0 ; pos_x < owner_width ; pos_x++) {
        for (int pos_y = 0 ; pos_y < owner_height ; pos_y++) {
            
            Window::Color selected;
            
            switch (GetTile(pos_x, pos_y)->CurrentState()) {
                case Tile::State::kAlive:       selected = Window::Color::kRed; break;
                case Tile::State::kDead:        selected = Window::Color::kBlack; break;
            }
            
            if (selected != prev) {
                
                wattroff(win, COLOR_PAIR(prev));
                wattron(win, COLOR_PAIR(selected));

            }
            
            prev = selected;
            
            mvwprintw(win, pos_y, pos_x, " ");

        }
    }
}

void Board::Impl::Toggle(int pos_x, int pos_y) {

    Tile* selected = GetTile(pos_x, pos_y);
    
    switch (selected->CurrentState()) {
        case Tile::State::kAlive: {
            
            selected->Update(Tile::State::kDead);
            selected->m_state = Tile::State::kDead;
            break;
        }
        case Tile::State::kDead: {
            
            selected->Update(Tile::State::kAlive);
            selected->m_state = Tile::State::kAlive;
            break;
        }
    }
}

void Board::Impl::Reset() {
    
    int owner_width = m_owner.GetWidth();
    int owner_height = m_owner.GetHeight();
    
    //Reset all of the tiles
    for (int pos_x = 0 ; pos_x < owner_width ; pos_x++) {
        for (int pos_y = 0 ; pos_y < owner_height ; pos_y++) {
            
            Tile& current = *GetTile(pos_x, pos_y);
            
            /*
             * Only the board should have direct access to both tile's properties,
             * and should not have a Reset function located at the Tile's class that
             * could be accessed from other places.
             */
            current.m_state = Tile::State::kDead;
            current.m_parallel->m_state = Tile::State::kDead;
            
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    
    int width = board.GetWidth();
    int height = board.GetHeight();
    
    //Draw all the tiles
    for (int pos_x = 0 ; pos_x < width ; pos_x++) {
        for (int pos_y = 0 ; pos_y < height ; pos_y++) {
     
            Tile::State current = board.GetTile(pos_x, pos_y)->CurrentState();
            std::cout << ((current == Tile::State::kAlive) ? "X" : ".");
            
        }
        std::cout << '\n';
    }
    
    return out;
}

#pragma mark - Board functions

Board* Board::CreateBoard(Board::Type type, int width, int height) {
    
    //Allocate accoding to type
    switch (type) {
        case Board::Type::kCircular:    return new CircularBoard(width, height);
        case Board::Type::kFlat:        return new FlatBoard(width, height);
    }
}

Board::Board(int width, int height) :
View(width, height),
m_pimpl(new Impl(*this))
{ }

Board::~Board() { }

Board::Block Board::GetBlock(const Tile& marker) const {
    return m_pimpl->GetBlock(marker);
}

void Board::AddRule(Rule* rule) {
    m_pimpl->AddRule(rule);
}

void Board::AddClassicRule(ClassicRule *rule) {
    m_pimpl->AddClassicRule(rule);
}

void Board::ClearRules() {
    m_pimpl->ClearRules();
}

void Board::Simulate() {
    m_pimpl->Simulate();
}

void Board::Toggle(int pos_x, int pos_y) {
    m_pimpl->Toggle(pos_x, pos_y);
}

void Board::Reset() {
    m_pimpl->Reset();
}

void Board::Resize(const Sizable& size) {

    //Store the previous size
    Sizable prev = Sizable(*this);
    
    SetHeight(size.GetHeight());
    SetWidth(size.GetWidth());
    
    //Apply changes
    m_pimpl->Resize(prev);
}

void Board::Draw(WINDOW* win) const {
    m_pimpl->Draw(win);
}

Tile* Board::GetTile(int pos_x, int pos_y) const {
    return m_pimpl->GetTile(pos_x, pos_y);
}


