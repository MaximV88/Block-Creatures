//
//  Game.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Game.hpp"
#include "Rule.hpp"

Game::Game() {
    
    m_board = Board::CreateBoard(Board::Type::kFlat, 10, 10);
    
    //Order of adding the rules is very important and is following instructions
    m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    for (size_t index = 0 ; index < 10 ; index++)
        m_board->Simulate();
    
}

Game::~Game() {
    
    delete m_board;
    
}