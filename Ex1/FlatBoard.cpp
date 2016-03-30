//
//  FlatBoard.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "FlatBoard.hpp"
#include "Tile.hpp"

FlatBoard::FlatBoard(int width, int height) :
Board(width, height)
{ }

Tile* FlatBoard::GetNeighbor(const Tile& marker, Board::Direction direction) const {
    
    /*
     * The flat board has well defined borders.
     * Edge tiles that want to reference the edge
     * will have NULL returned.
     */
    switch (direction) {
        case Board::Direction::kTop: {
            
            //Check illigal request
            if (marker.pos_y == 0)
                return NULL;
            
            return GetTile(marker.pos_x, marker.pos_y - 1);
        }
        case Board::Direction::kBottom: {
            
            //Check illigal request
            if (marker.pos_y == GetHeight() - 1)
                return NULL;
            
            return GetTile(marker.pos_x, marker.pos_y + 1);
        }
        case Board::Direction::kRight: {
            
            //Check illigal request
            if (marker.pos_x == GetWidth() - 1)
                return NULL;
            
            return GetTile(marker.pos_x + 1, marker.pos_y);
        }
        case Board::Direction::kLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0)
                return NULL;
            
            return GetTile(marker.pos_x - 1, marker.pos_y);
        }
        case Board::Direction::kTopLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0 ||
                marker.pos_y == 0)
                return NULL;
            
            return GetTile(marker.pos_x - 1, marker.pos_y - 1);
        }
        case Board::Direction::kTopRight: {
            
            //Check illigal request
            if (marker.pos_x == GetWidth() -1 ||
                marker.pos_y == 0)
                return NULL;
            
            return GetTile(marker.pos_x + 1, marker.pos_y - 1);
        }
        case Board::Direction::kBottomLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0 ||
                marker.pos_y == GetHeight() - 1)
                return NULL;
            
            return GetTile(marker.pos_x - 1, marker.pos_y + 1);
        }
        case Board::Direction::kBottomRight: {
            
            //Check illigal request
            if (marker.pos_x == GetWidth() - 1 ||
                marker.pos_y == GetHeight() - 1)
                return NULL;
            
            return GetTile(marker.pos_x + 1, marker.pos_y + 1);
        }
    }
}
