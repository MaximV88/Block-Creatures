//
//  StagnationRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "StagnationRule.hpp"
#include "Tile.hpp"

bool StagnationRule::Apply(Board::Block block) const {
    
    //Check to see if the block contains exactly 2 living creatures
    size_t alive = 0;
    
    if (block.top_left->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.top_right->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.bottom_left->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.bottom_right->CurrentState() == Tile::State::kAlive) ++alive;

    //Stop applying rules to block if it has exactly 2 alive
    return (alive == 2);
}