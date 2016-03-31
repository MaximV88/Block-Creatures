//
//  OverpopulationClassicRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "OverpopulationClassicRule.hpp"
#include "Tile.hpp"

bool OverpopulationClassicRule::Apply(Tile& marker) const {
    
    //Applies towards living tiles only
    if (marker.CurrentState() == Tile::State::kAlive &&
        AliveNeighbors(marker) >= 4) {
        
        //Each cell with four or more neighbors dies, as if by overpopulation
        marker.Update(Tile::State::kDead);
        return true;
    }
    
    //No changes made - continue to other rules
    return false;
}