//
//  Rule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Rule.hpp"
#include "RotationRule.hpp"
#include "ReversalRule.hpp"
#include "StagnationRule.hpp"

Rule* Rule::CreateRule(Rule::Type type) {
    
    //Allocate accoding to type
    switch (type) {
        case kStagnation:   return new StagnationRule();
        case kRotation:     return new RotationRule();
        case kReversal:     return new ReversalRule();
    }
}

Rule::~Rule() { }