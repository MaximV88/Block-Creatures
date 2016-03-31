//
//  SolitudeClassicRule.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef SolitudeClassicRule_hpp
#define SolitudeClassicRule_hpp
#include "ClassicRule.hpp"

class SolitudeClassicRule : public ClassicRule {
public:
    
    /**
     * Requests to apply rule on the input tile. If any changes
     * occured the ClassicRule will stop to apply other
     * rules.
     *
     * @param marker The tile to process.
     * @return  True to stop processing following rules
     *          for the current simulation, False to continue.
     */
    bool Apply(Tile& marker) const;
    
};

#endif /* SolitudeClassicRule_hpp */
