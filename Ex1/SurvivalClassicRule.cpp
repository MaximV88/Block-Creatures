//
//  SurvivalClassicRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "SurvivalClassicRule.hpp"
#include "Tile.hpp"

bool SurvivalClassicRule::Apply(Tile& marker) const {
    
    //Applies towards living tiles only
    if (marker.CurrentState() == Tile::State::kAlive) {
        
        int living_neighbors = AliveNeighbors(marker);
        
        if (living_neighbors == 2 || living_neighbors == 3) {
            
            //Each cell with two or three neighbors survives - stop applying other rules
            return true;
        }
    }
    
    //No changes made - continue to other rules
    return false;
}