//
//  Tile.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp
#include <stdio.h>

class Tile {
public:
    
    enum State {
        kAlive,
        kDead
    };
    
    Tile(size_t pos_x, size_t pos_y);
    
private:
    
    Tile::State m_state;
    const size_t m_pos_x;
    const size_t m_pos_y;
    
};

#endif /* Tile_hpp */
