//
//  AboutScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include <unistd.h>
#include "AboutScene.hpp"
#include "EntranceScene.hpp"
#include "Window.hpp"
#include "Director.hpp"

#include "Board.hpp"
#include "Label.hpp"

#include "Rule.hpp"
#include "ClassicRule.hpp"
#include "CreationistRule.hpp"

void AboutScene::OnEntrance(Window& win) {

    int board_width = win.GetWidth() / 2;
    int board_height = (win.GetHeight() / 2) + 1;
    
    //Create boards to populate
    m_top_left = Board::CreateBoard(Board::Type::kFlat, board_width, board_height);
    m_top_right = Board::CreateBoard(Board::Type::kCircular, board_width, board_height);
    m_bottom_left = Board::CreateBoard(Board::Type::kFlat, board_width, board_height);
    m_bottom_right = Board::CreateBoard(Board::Type::kCircular, board_width, board_height);

    //Randomize all
    RandomizeBoardPopulation(m_top_left);
    RandomizeBoardPopulation(m_top_right);
    RandomizeBoardPopulation(m_bottom_left);
    RandomizeBoardPopulation(m_bottom_right);

    //Apply rules
    m_top_left->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kSolitude));
    m_top_left->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kOverpopulation));
    m_top_left->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kSurvival));
    m_top_left->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kPopulation));
    
    m_bottom_right->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kSolitude));
    m_bottom_right->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kOverpopulation));
    m_bottom_right->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kSurvival));
    m_bottom_right->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kPopulation));
    
    m_bottom_left->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_bottom_left->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_bottom_left->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    m_top_right->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_top_right->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_top_right->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    //Add to view
    win.AddView(*m_top_left, 0, 0);
    win.AddView(*m_top_right, win.GetWidth() / 2, 0);
    win.AddView(*m_bottom_left, 0, win.GetHeight() / 2);
    win.AddView(*m_bottom_right, win.GetWidth() / 2, win.GetHeight() / 2);
    
    //Add a fancy label
    m_about = new Label("Created by Maxim Vainshtein and Kati Adler.", true);
    win.AddView(*m_about,
                (win.GetWidth() - m_about->GetWidth()) / 2,
                (win.GetHeight() - m_about->GetHeight()) / 2);
    
    //Add a regular one
    m_instructions = new Label("F1: Return to main menu.");
    win.AddView(*m_instructions, 0, LINES - 1);
}

void AboutScene::OnDismiss(Window& win) {
    
    if (m_top_left) delete m_top_left;
    if (m_top_right) delete m_top_right;
    if (m_bottom_left) delete m_bottom_left;
    if (m_bottom_right) delete m_bottom_right;
    if (m_about) delete m_about;
    if (m_instructions) delete m_instructions;
}

void AboutScene::OnUpdate(Window& win) {
    
    //Simulate all boards
    m_top_left->Simulate();
    m_top_right->Simulate();
    m_bottom_left->Simulate();
    m_bottom_right->Simulate();
    
    usleep(300000);
}

void AboutScene::OnKeyboardEvent(Window& win, int input) {
    
    switch (input) {
        case KEY_F(1): {
            
            Director::SharedDirector().Present(new EntranceScene());
            break;
        }
        default: break;
    }
}

void AboutScene::RandomizeBoardPopulation(Board *board) {
    
    board->AddRule(new CreationistRule(0.5));
    board->Simulate();
    board->ClearRules();
}
