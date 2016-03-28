//
//  Board.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Board.hpp"
#include "Rule.hpp"
#include "Tile.hpp"
#include "FlatBoard.hpp"
#include "CircularBoard.hpp"

Board* Board::CreateBoard(Board::Type type, size_t width, size_t height) {
    
    //Allocate accoding to type
    switch (type) {
        case Board::Type::kCircular:    return new CircularBoard(width, height);
        case Board::Type::kFlat:        return new FlatBoard(width, height);
    }
}

Board::Board(size_t width, size_t height) :
m_width(width),
m_height(height) {

    bool initialized = false;
    while (!initialized) {
        
        try {
            
            //Allocate heap memory
            m_board = InitializeBoard(width, height);
            
            initialized = true;
            
        } catch (...) {
            
            //Retry
            initialized = false;
            
        }
    }
}

Board::~Board() {
    
    DeallocateBoard(m_board.first, m_width, m_height);
    DeallocateBoard(m_board.second, m_width, m_height);
    
    //Delete all rules
    for (std::vector<Rule*>::iterator start = m_rules.begin(), end = m_rules.end() ;
         start != end ;
         start++)
        delete *start;
    
}

void Board::AddRule(Rule *rule) {
    
    //Not using smart pointers due to older version of C++
    m_rules.push_back(rule);
    
}

void Board::Simulate() {

    //Increment generation index to know which lines to follow
    ++m_generation;

    /*
     * Since the blocks are at size 2x2 to
     * avoid triggering each block twice iterate
     * at jumps of 2.
     */
    for (size_t width = 0 ; width < m_width ; width += 2) {
        for (size_t height = 0 ; height < m_height ; height += 2) {
            
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
    
    //Apply all changes on the parallel tiles onto the current ones by switching boards
    Tile** temp = m_board.first;
    m_board.first = m_board.second;
    m_board.second = temp;
    
}

Board::Block Board::GetBlock(const Tile &marker) const {
    
    Block result = { NULL, NULL, NULL, NULL };
    
    switch (LocalPositionInBlock(marker)) {
        case kTopLeft: {
        
            result.top_left = GetTile(marker.pos_x, marker.pos_y);
            result.top_right = GetNeighbor(marker, kRight);
            result.bottom_left = GetNeighbor(marker, kBottom);
            result.bottom_right = GetNeighbor(marker, kBottomRight);
            
            break;
        }
        case kTopRight: {
            
            result.top_left = GetNeighbor(marker, kLeft);
            result.top_right = GetTile(marker.pos_x, marker.pos_y);
            result.bottom_left = GetNeighbor(marker, kBottomLeft);
            result.bottom_right = GetNeighbor(marker, kBottom);
            
            break;
        }
        case kBottomLeft: {
            
            result.top_left = GetNeighbor(marker, kTop);
            result.top_right = GetNeighbor(marker, kTopRight);
            result.bottom_left = GetTile(marker.pos_x, marker.pos_y);
            result.bottom_right = GetNeighbor(marker, kRight);
            
            break;
        }
        case kBottomRight: {
            
            result.top_left = GetNeighbor(marker, kTopLeft);
            result.top_right = GetNeighbor(marker, kTop);
            result.bottom_left = GetNeighbor(marker, kLeft);
            result.bottom_right = GetTile(marker.pos_x, marker.pos_y);
            
            break;
        }
        //All fields should stay null
        default: break;
    }
    
    return result;
}

Tile* Board::GetTile(size_t pos_x, size_t pos_y) const {
    
    //Check valid position
    if (pos_x >= m_width ||
        pos_y >= m_height)
        return NULL;
    
    return m_board.first[Index(pos_x, pos_y)];
}

size_t Board::Index(size_t pos_x, size_t pos_y) const {
    
    /*
     * The 2 dimentional array is treated as a 
     * one dimentional array to avoid having an
     * array of arrays.
     */
    return pos_x + m_width * pos_y;
}

Board::board_t Board::InitializeBoard(size_t width, size_t height) const {
    
    //The board consists of heap allocated tiles
    Tile** board_first = new Tile*[width * height];
    Tile** board_second = new Tile*[width * height];
    
    //Each tile needs to be initialized
    for (size_t pos_x = 0 ; pos_x < width ; pos_x++) {
        for (size_t pos_y = 0 ; pos_y < height ; pos_y++) {
            
            Tile* current = new Tile(pos_x, pos_y, this);
            Tile* parallel = new Tile(pos_x, pos_y, this);
            
            //Create links for each other
            current->m_parallel = parallel;
            parallel->m_parallel = current;
            
            board_first[Index(pos_x, pos_y)] = current;
            board_second[Index(pos_x, pos_y)] = parallel;
            
        }
    }
    
    return Board::board_t(board_first, board_second);
}

void Board::DeallocateBoard(Tile **board, size_t width, size_t height) const {
    
    //Remove heap allocated memory
    if (board) {
        
        for (size_t index = 0 ; index < height * width ; index++)
            delete board[index];
        
        delete [] board;
        
    }
}

Board::Direction Board::LocalPositionInBlock(const Tile& marker) const {
    
    //Assign tiles according to generation number
    if (m_generation % 2 == 0) {
        
        /*
         * For even generations the red lines should be followed.
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
    else {
        
        /*
         * For odd generations the blue lines should be followed.
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
}
