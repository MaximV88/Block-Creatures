//
//  PopulationClassicRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "PopulationClassicRule.hpp"
#include "Tile.hpp"

bool PopulationClassicRule::Apply(Tile& marker) const {
    
    //Applies towards living tiles only
    if (marker.CurrentState() == Tile::State::kDead &&
        AliveNeighbors(marker) == 3) {
        
        //Each cell with three neighbors becomes populated
        marker.Update(Tile::State::kAlive);
        return true;
    }
    
    //No changes made - continue to other rules
    return false;
}