//
//  Board.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp
#include "View.hpp"
#include <vector>
#include <ncurses.h>
#include <iostream>
class Tile;
class Rule;

/**
 * The Board holds Tile objects, and is responsible for
 * returning blocks and tiles according to direction.
 * <br>
 * The coordinate system is structured by having (0,0) for the upper left corner.
 */
class Board : public View {
public:
    
    /**
     * Possible directions for each tile to 
     * reference another tile.
     */
    enum Direction {
        kTop,
        kBottom,
        kLeft,
        kRight,
        kTopRight,
        kTopLeft,
        kBottomRight,
        kBottomLeft
    };
    
    /**
     * Board behavior types.
     */
    enum Type {
        kFlat,
        kCircular
    };
    
    /**
     * Represents a block as the excercise states.
     */
    struct Block {
        Tile* top_left;
        Tile* top_right;
        Tile* bottom_left;
        Tile* bottom_right;
    };
    
    /**
     * Returns a heap allocated board of specified type.
     *
     * @param type The type of board to create.
     * @return Heap allocated board.
     */
    static Board* CreateBoard(Board::Type type, int width, int height);
    
    /**
     * Destructor.
     */
    virtual ~Board();
    
    virtual Tile* GetNeighbor(const Tile& marker, Direction direction) const = 0;
    virtual Block GetBlock(const Tile& marker) const;
    
    void AddRule(Rule* rule);
    void ClearRules();
    void Simulate();
    void Resize(const Sizable& size);
    
    void Draw(WINDOW* win) const;
    
    friend std::ostream& operator<<(std::ostream& out, const Board& board);

protected:
    
    /**
     * Constructor.
     *
     * @param width The width the board should have.
     * @param height The height the board should have.
     */
    Board(int width, int height);
    
    /**
     * Returns the tile at the specified location.
     * If no tile exists, returns NULL.
     *
     * @param pos_x The X location of the requested tile.
     * @param pos_y The Y location of the requested tile.
     * @return The tile that is stored in the board. May return NULL.
     */
    Tile* GetTile(int pos_x, int pos_y) const;
    
private:
    
    typedef std::pair<Tile**, Tile**> board_t;
    
    int Index(int pos_x, int pos_y) const;
    board_t InitializeBoard(int width, int height) const;
    Direction LocalPositionInBlock(const Tile& marker) const;
    void DeallocateBoard(Tile** board, int width, int height) const;
    
    board_t m_board;
    int m_generation;
    std::vector<Rule*> m_rules;
    
};

#endif /* Board_hpp */
