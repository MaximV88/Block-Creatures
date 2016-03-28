//
//  Tile.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp
#include "Board.hpp"

class Tile {
public:
    
    enum State {
        kAlive,
        kDead
    };
    
    Tile(size_t pos_x, size_t pos_y, const Board* board, Tile* parallel, Tile::State state = Tile::State::kDead);
        
    void Toggle();
    
    Tile::State CurrentState() const;
    
    Tile* Neighbor(Board::Direction direction) const;

    const size_t pos_x;
    const size_t pos_y;
    
private:
    
    ///Stores the state of the tile.
    Tile::State m_state;
    
    ///Stores the containing board.
    const Board& m_board;
    
    ///Stores the parallel tile.
    Tile& m_parallel;

};

#endif /* Tile_hpp */
