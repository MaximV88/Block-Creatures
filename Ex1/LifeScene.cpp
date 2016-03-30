//
//  LifeScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "LifeScene.hpp"
#include "Board.hpp"
#include "Window.hpp"

#include "Rule.hpp"
#include "CreationistRule.hpp"

LifeScene::LifeScene() :
m_board(NULL) {

    m_board = Board::CreateBoard(Board::Type::kFlat, 100, 80);
    
    //The first stage needs to have the board randomly initialized to 0 or 1
    m_board->AddRule(new CreationistRule(0.5));
    m_board->Simulate();
    m_board->ClearRules();
    
    //Order of adding the rules is very important and is following instructions
    m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
}

LifeScene::~LifeScene() {
    if (m_board) delete m_board;    
}

void LifeScene::OnEntrance(Window& win) {
  //  win.Resize(Sizable(100, 80));
    win.AddView(*m_board, 0, 0);
    
}

void LifeScene::OnDismiss(Window& win) {
    win.RemoveView(*m_board);
}

void LifeScene::OnUpdate() {
    static size_t generation = 0;
    m_board->Simulate();
    mvprintw(0, 0, "Generation: %lu", ++generation);
    usleep(100000);
}