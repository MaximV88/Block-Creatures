//
//  ClassicRule.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef ClassicRule_hpp
#define ClassicRule_hpp
class Tile;

/**
 * Although not in the excercise, these were added to see how
 * Game of life behaves. 
 */
class ClassicRule {
public:
    
    enum Type {
        kSolitude
    };
    
    static ClassicRule* CreateClassicRule(ClassicRule::Type type);
    
    virtual ~ClassicRule();
    
    /**
     * Requests to apply rule on the input tile. If any changes
     * occured the ClassicRule will stop to apply other
     * rules.
     *
     * @param marker The tile to process.
     * @return  True to stop processing following rules
     *          for the current simulation, False to continue.
     */
    virtual bool Apply(Tile& marker) const = 0;
    
protected:

    /** 
     * Returns the number of living neighbors.
     *
     * @param The tile to check for living neighbors.
     * @return Number of living neighbors.
     */
    int AliveNeighbors(const Tile& marker) const;
    
    
    
};
#endif /* ClassicRule_hpp */
