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
    
    enum Type {
        kRotation,
        kReversal,
        kStagnation
    };
    
    static Rule* CreateRule(Rule::Type type);
    
    virtual ~Rule();
    
    /**
     * Applies the rule on the given block.
     * Decides if to continue processing other rules.
     *
     * @param block The block to apply the rule on.
     * @return  True to stop processing following rules
     *          for the current simulation, False to continue.
     */
    virtual bool Apply(Board::Block block) const = 0;
    
};

#endif /* Rule_hpp */
