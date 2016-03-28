//
//  RotationRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "RotationRule.hpp"

bool RotationRule::Apply(Board::Block block) const {
    
    //Check to see if the block contains exactly 3 living creatures
    size_t alive = 0;
    
    if (block.top_left->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.top_right->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.bottom_left->CurrentState() == Tile::State::kAlive) ++alive;
    if (block.bottom_right->CurrentState() == Tile::State::kAlive) ++alive;
    
    if (alive == 3) {
        
        //Get all values
        Tile::State top_left = block.top_left->CurrentState();
        Tile::State top_right = block.top_right->CurrentState();
        Tile::State bottom_left = block.bottom_left->CurrentState();
        Tile::State bottom_right = block.bottom_right->CurrentState();
        
        //Toggle them manually because rotation requires these values as well
        top_left = (top_left == Tile::State::kAlive) ? Tile::State::kDead: Tile::State::kDead;
        top_right = (top_right == Tile::State::kAlive) ? Tile::State::kDead: Tile::State::kDead;
        bottom_left = (bottom_left == Tile::State::kAlive) ? Tile::State::kDead: Tile::State::kDead;
        bottom_right = (bottom_right == Tile::State::kAlive) ? Tile::State::kDead: Tile::State::kDead;

        //Set values according to rotation
        block.top_left->Update(bottom_right);
        block.top_right->Update(bottom_left);
        block.bottom_left->Update(top_right);
        block.bottom_right->Update(top_left);
        
        return true;
    }
    
    //No changes made, continue to other rules
    return false;
}