//
//  Rule.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp
#include "Tile.hpp"

class Rule {
public:
    
    virtual Tile::State Apply(Board::Block) const = 0;
    
};

#endif /* Rule_hpp */
