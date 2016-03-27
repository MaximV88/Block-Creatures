//
//  Tile.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(size_t pos_x, size_t pos_y, Tile::State state) :
pos_x(pos_x),
pos_y(pos_y),
m_state(state)
{ }

void Tile::Toggle() {
    
    //Leaves possibility for more complicated state transitions
    switch (m_state) {
        case Tile::State::kAlive:   m_state = kDead; break;
        case Tile::State::kDead:    m_state = kAlive; break;
    }
}

Tile::State Tile::CurrentState() const {

    //Return a copy of the state to prevent changes
    return m_state;
}

