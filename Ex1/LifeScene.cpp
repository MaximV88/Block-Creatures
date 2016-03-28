//
//  LifeScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "LifeScene.hpp"
#include "Board.hpp"
#include "Rule.hpp"
#include <ncurses.h>

LifeScene::LifeScene() :
m_board(NULL)
{ }

void LifeScene::OnEntrance() {
    
    //Validate that ncurses is initialize
    if (!stdscr) initscr();
    
    if (m_board) delete m_board;
    
    m_board = Board::CreateBoard(Board::Type::kFlat, 10, 10);
    
    //Order of adding the rules is very important and is following instructions
    m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    for (size_t index = 0 ; index < 10 ; index++) {
        
        m_board->Simulate();
        
    //    sleep(1);
        
    }
    
}

void LifeScene::OnDismiss() {
    
    delete m_board;

}