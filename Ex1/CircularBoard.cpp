//
//  CircularBoard.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "CircularBoard.hpp"

CircularBoard::CircularBoard(size_t width, size_t height) :
Board(width, height)
{ }

Tile* CircularBoard::GetNeighbor(const Tile& marker, Board::Direction direction) const {
    
    /*
     * The circular board doesnt have any borders.
     * Edge tiles that want to reference the edge
     * will have the opposite tile in the map returned.
     */
    switch (direction) {
        case Board::Direction::kTop: {
            
            //Check illigal request
            if (marker.pos_y == 0)
                return &GetTile(marker.pos_x, m_height - 1);
            
            return &GetTile(marker.pos_x, marker.pos_y - 1);
        }
        case Board::Direction::kBottom: {
            
            //Check illigal request
            if (marker.pos_y == m_height - 1)
                return &GetTile(marker.pos_x, 0);
            
            return &GetTile(marker.pos_x, marker.pos_y + 1);
        }
        case Board::Direction::kRight: {
            
            //Check illigal request
            if (marker.pos_x == m_width - 1)
                return &GetTile(0, marker.pos_y);
            
            return &GetTile(marker.pos_x + 1, marker.pos_y);
        }
        case Board::Direction::kLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0)
                return &GetTile(m_width - 1, marker.pos_y);
            
            return &GetTile(marker.pos_x - 1, marker.pos_y);
        }
        case Board::Direction::kTopLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0 ||
                marker.pos_y == 0)
                return &GetTile(m_width - 1, m_height - 1);
            
            return &GetTile(marker.pos_x - 1, marker.pos_y - 1);
        }
        case Board::Direction::kTopRight: {
            
            //Check illigal request
            if (marker.pos_x == m_width -1 ||
                marker.pos_y == 0)
                return &GetTile(0, m_height - 1);
            
            return &GetTile(marker.pos_x + 1, marker.pos_y - 1);
        }
        case Board::Direction::kBottomLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0 ||
                marker.pos_y == m_height - 1)
                return &GetTile(m_width - 1, 0);
            
            return &GetTile(marker.pos_x - 1, marker.pos_y + 1);
        }
        case Board::Direction::kBottomRight: {
            
            //Check illigal request
            if (marker.pos_x == m_width - 1 ||
                marker.pos_y == m_height - 1)
                return &GetTile(0, 0);
            
            return &GetTile(marker.pos_x + 1, marker.pos_y + 1);
        }
    }
}

Board::Block CircularBoard::GetBlock(const Tile &marker) const {
    
}