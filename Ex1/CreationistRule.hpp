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
    bool Apply(Board::Block block) const;

    
private:
    
    float m_probability;
    
};

#endif /* CreationistRule_hpp */
