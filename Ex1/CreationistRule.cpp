//
//  CreationistRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "CreationistRule.hpp"
#include <ctime>

bool ThrowDice(float probability) { return (double)std::rand() / RAND_MAX < probability; }

CreationistRule::CreationistRule(float probability) :
m_probability(probability) {

    // use current time as seed for random generator
    std::srand((unsigned)std::time(0));

}

bool CreationistRule::Apply(Board::Block block) const {

    //There is a chance that spontanous life appears
    
    if (ThrowDice(m_probability)) block.top_left->Update(Tile::State::kAlive);
    if (ThrowDice(m_probability)) block.top_right->Update(Tile::State::kAlive);
    if (ThrowDice(m_probability)) block.bottom_left->Update(Tile::State::kAlive);
    if (ThrowDice(m_probability)) block.bottom_right->Update(Tile::State::kAlive);

    //The rule is above all and nothing else may evolve further on
    return true;
}
