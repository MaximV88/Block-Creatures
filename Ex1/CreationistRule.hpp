//
//  CreationistRule.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef CreationistRule_hpp
#define CreationistRule_hpp
#include "Rule.hpp"

class CreationistRule : public Rule {    
public:
    
    CreationistRule(float probability);
    
    /**
     * Applies the rule on the given block.
     * Decides if to continue processing other rules.
     *
     * @param block The block to apply the rule on.
     * @return  True to stop processing following rules
     *          for the current simulation, False to continue.
     */
    bool Apply(Board::Block block) const;

    
private:
    
    float m_probability;
    
};

#endif /* CreationistRule_hpp */
