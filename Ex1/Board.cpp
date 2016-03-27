//
//  Board.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Board.hpp"

Board::Board(size_t width, size_t height) :
m_width(width),
m_height(height),
m_board(InitializeBoard(width, height))
{ }

Board::~Board() {
    
    //Remove heap allocated memory
    if (m_board) {
        
        for (size_t index = 0 ; index < m_height * m_width ; index++)
            delete m_board[index];
        
        delete [] m_board;
        
    }
}

size_t Board::Index(size_t pos_x, size_t pos_y) const {
    
    /*
     * The 2 dimentional array is treated as a 
     * one dimentional array to avoid having an
     * array of arrays.
     */
    return pos_x + m_width * pos_y;
}

Tile** Board::InitializeBoard(size_t width, size_t height) const {
    
    //The board consists of heap allocated tiles
    Tile** board = new Tile*[width * height];
    
    //Each tile needs to be initialized
    for (size_t pos_x = 0 ; pos_x < width ; pos_x++)
        for (size_t pos_y = 0 ; pos_y < height ; pos_y++)
            board[Index(pos_x, pos_y)] = new Tile(pos_x, pos_y);
    
    return board;
}

Tile& Board::GetTile(size_t pos_x, size_t pos_y) const {
    
    //Return a reference to avoid accidental deletion
    return *(m_board[Index(pos_x, pos_y)]);
}