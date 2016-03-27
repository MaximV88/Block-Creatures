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
#include "Tile.hpp"

/**
 * The Board holds Tile objects, and is responsible for
 * returning blocks and tiles according to direction.
 * <br>
 * The coordinate system is structured by having (0,0) for the upper left corner.
 */
class Board {
public:
    
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
    
    struct Block {
        Tile* top_left;
        Tile* top_right;
        Tile* bottom_left;
        Tile* bottom_right;
    };
    
    Board(size_t width, size_t height);
    virtual ~Board();
    
    virtual Tile* GetNeighbor(const Tile& marker, Direction direction) const = 0;
    virtual Block GetBlock(const Tile& marker) const;
    
    void Simulate();
    
protected:
    
    Tile& GetTile(size_t pos_x, size_t pos_y) const;
    
    size_t m_width;
    size_t m_height;
    
private:
    
    size_t Index(size_t pos_x, size_t pos_y) const;
    Tile** InitializeBoard(size_t width, size_t height) const;
    
    Tile** m_board;    
    size_t m_generation;

};

#endif /* Board_hpp */
