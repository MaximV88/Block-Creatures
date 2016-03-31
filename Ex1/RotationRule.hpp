//
//  RotationRule.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef RotationRule_hpp
#define RotationRule_hpp
#include "Rule.hpp"

class RotationRule : public Rule {
public:
    
    /**
     * Applies the rule on the given block.
     * Decides if to continue processing other rules.
     *
     * @param block The block to apply the rule on.
     * @return  True to stop processing following rules
     *          for the current simulation, False to continue.
     */
    bool Apply(Board::Block block) const;

    
};

#endif /* RotationRule_hpp */
