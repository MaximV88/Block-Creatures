//
//  Board.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp
#include <stdio.h>
#include <vector>
class Tile;
class Rule;

/**
 * The Board holds Tile objects, and is responsible for
 * returning blocks and tiles according to direction.
 * <br>
 * The coordinate system is structured by having (0,0) for the upper left corner.
 */
class Board {
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
    static Board* CreateBoard(Board::Type type, size_t width, size_t height);
    
    /**
     * Constructor.
     *
     * @param width The width the board should have.
     * @param height The height the board should have.
     */
    Board(size_t width, size_t height);
    
    /**
     * Destructor.
     */
    virtual ~Board();
    
    virtual Tile* GetNeighbor(const Tile& marker, Direction direction) const = 0;
    virtual Block GetBlock(const Tile& marker) const;
    
    void AddRule(Rule* rule);
    void Simulate();
    
protected:
    
    /**
     * Returns the tile at the specified location.
     * If no tile exists, returns NULL.
     *
     * @param pos_x The X location of the requested tile.
     * @param pos_y The Y location of the requested tile.
     * @return The tile that is stored in the board. May return NULL.
     */
    Tile* GetTile(size_t pos_x, size_t pos_y) const;
    
    ///Stores the width of the board
    size_t m_width;
    
    ///Stores the height of the board
    size_t m_height;
    
private:
    
    typedef std::pair<Tile**, Tile**> board_t;
    
    size_t Index(size_t pos_x, size_t pos_y) const;
    board_t InitializeBoard(size_t width, size_t height) const;
    Direction LocalPositionInBlock(const Tile& marker) const;
    void DeallocateBoard(Tile** board, size_t width, size_t height) const;
    
    board_t m_board;
    size_t m_generation;
    std::vector<Rule*> m_rules;
    
};

#endif /* Board_hpp */
