//
//  CircularBoard.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "CircularBoard.hpp"
#include "Tile.hpp"

CircularBoard::CircularBoard(int width, int height) :
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
                return GetTile(marker.pos_x, GetHeight() - 1);
            
            return GetTile(marker.pos_x, marker.pos_y - 1);
        }
        case Board::Direction::kBottom: {
            
            //Check illigal request
            if (marker.pos_y == GetHeight() - 1)
                return GetTile(marker.pos_x, 0);
            
            return GetTile(marker.pos_x, marker.pos_y + 1);
        }
        case Board::Direction::kRight: {
            
            //Check illigal request
            if (marker.pos_x == GetWidth() - 1)
                return GetTile(0, marker.pos_y);
            
            return GetTile(marker.pos_x + 1, marker.pos_y);
        }
        case Board::Direction::kLeft: {
            
            //Check illigal request
            if (marker.pos_x == 0)
                return GetTile(GetWidth() - 1, marker.pos_y);
            
            return GetTile(marker.pos_x - 1, marker.pos_y);
        }
        case Board::Direction::kTopLeft: {
            
            //Assured to have a value - no need to check for NULL
            Tile* left = GetNeighbor(marker, Board::Direction::kLeft);
            
            return GetNeighbor(*left, Board::Direction::kTop);
        }
        case Board::Direction::kTopRight: {
            
            //Assured to have a value - no need to check for NULL
            Tile* right = GetNeighbor(marker, Board::Direction::kRight);
            
            return GetNeighbor(*right, Board::Direction::kTop);
        }
        case Board::Direction::kBottomLeft: {
            
            //Assured to have a value - no need to check for NULL
            Tile* left = GetNeighbor(marker, Board::Direction::kLeft);
            
            return GetNeighbor(*left, Board::Direction::kBottom);
        }
        case Board::Direction::kBottomRight: {
            
            //Assured to have a value - no need to check for NULL
            Tile* right = GetNeighbor(marker, Board::Direction::kRight);
            
            return GetNeighbor(*right, Board::Direction::kBottom);
        }
    }
}
