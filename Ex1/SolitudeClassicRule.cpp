//
//  SolitudeClassicRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "SolitudeClassicRule.hpp"
#include "Tile.hpp"

bool SolitudeClassicRule::Apply(Tile& marker) const {
    
    //Applies towards living tiles only
    if (marker.CurrentState() == Tile::State::kAlive &&
        AliveNeighbors(marker) <= 1) {
        
        //Each cell with one or no neighbors dies, as if by solitude
        marker.Update(Tile::State::kDead);
        return true;
    }
    
    //No changes made - continue to other rules
    return false;
}