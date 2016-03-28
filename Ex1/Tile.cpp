//
//  Tile.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Tile.hpp"
#include "Board.hpp"

Tile::Tile(size_t pos_x,
           size_t pos_y,
           const Board* board,
           Tile::State state) :
pos_x(pos_x),
pos_y(pos_y),
m_board(*board),
m_parallel(NULL),
m_state(state)
{ }

void Tile::Toggle() {
    
    //Leaves possibility for more complicated state transitions
    switch (m_state) {
        case Tile::State::kAlive:   m_parallel->m_state = kDead; break;
        case Tile::State::kDead:    m_parallel->m_state = kAlive; break;
    }
}

void Tile::Update(Tile::State state) {
    
    //All updates go to the parallel tile
    m_parallel->m_state = state;
}

Tile::State Tile::CurrentState() const {

    //Return a copy of the state to prevent changes
    return m_state;
}

Tile* Tile::Neighbor(Board::Direction direction) const {
    
    //Uses board's polymorphism to get neighbor by specified behavior
    return m_board.GetNeighbor(*this, direction);
}