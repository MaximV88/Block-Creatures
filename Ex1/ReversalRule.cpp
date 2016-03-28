//
//  ReversalRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "ReversalRule.hpp"
#include "Tile.hpp"

bool ReversalRule::Apply(Board::Block block) const {

    //Check to see if the block contains 0,1 or 4 living creatures
    size_t alive = 0;
    
    if (block.top_left->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.top_right->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.bottom_left->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.bottom_right->CurrentState() == Tile::State::kAlive) ++alive;
    
    //As per rule description
    if (alive == 0 ||
        alive == 1 ||
        alive == 4) {
        
        block.top_left->Toggle();
        block.top_right->Toggle();
        block.bottom_left->Toggle();
        block.bottom_right->Toggle();
        return true;
    }
    
    //No changes made, continue to other rules
    return false;
}