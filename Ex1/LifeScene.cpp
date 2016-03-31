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
#include "Label.hpp"
#include "Director.hpp"
#include "EntranceScene.hpp"
#include "Settings.hpp"
#include <ncurses.h>

#include "Rule.hpp"
#include "CreationistRule.hpp"

LifeScene::LifeScene() :
m_board(NULL),
m_top_label(NULL),
m_bottom_label(NULL),
m_generation(0),
m_play(true),
m_iteration_speed(100000) {

    //Create board type according to specified setting
    m_board = Board::CreateBoard(Settings::SharedSettings().board_type, 0, 0);
}

LifeScene::~LifeScene() {
    if (m_board) delete m_board;
    if (m_top_label) delete m_top_label;
    if (m_bottom_label) delete m_bottom_label;
}

void LifeScene::OnEntrance(Window& win) {
    
    m_board->Resize(win);
    
    //The first stage needs to have the board randomly initialized to 0 or 1
    m_board->AddRule(new CreationistRule(0.5));
    m_board->Simulate();
    m_board->ClearRules();
    
    //Order of adding the rules is very important and is following instructions
    m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    win.AddView(*m_board, 0, 0);
    
    m_top_label = new Label("Generation: 0");
    win.AddView(*m_top_label, 0, 0);
    
    m_bottom_label = new Label("Up/Down: Change speed. SPACE: Pause. F1: Return to previous menu.");
    win.AddView(*m_bottom_label, 0, LINES - 1);
    
}

void LifeScene::OnDismiss(Window& win) {

}

void LifeScene::OnUpdate(Window& win) {

    //Simulate a generation and increment the count for display
    if (m_play) { m_board->Simulate(); ++m_generation; };
    
    m_top_label->Update(std::string("Generation: ") + std::to_string(m_generation));

    usleep(m_iteration_speed);
}

void LifeScene::OnKeyboardEvent(Window& win, int input) {
    
    switch (input) {
        case KEY_F(1): {
            
            Director::SharedDirector().Present(new EntranceScene());
            break;
        }
        case KEY_UP: {
            
            if (m_iteration_speed < 60000) m_iteration_speed = 60000;

            m_iteration_speed -= 20000;
            break;
        }
        case KEY_DOWN: {
            
            m_iteration_speed += 20000;
            break;
        }
        case ' ': {
            
            m_play = !m_play;
            break;
        }
        //Dont do anything otherwise
        default: break;
    }
}