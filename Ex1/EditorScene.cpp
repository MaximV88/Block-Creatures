//
//  EditorScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "EditorScene.hpp"
#include "Window.hpp"
#include "Board.hpp"
#include "Rule.hpp"
#include "ClassicRule.hpp"
#include "Director.hpp"
#include "EntranceScene.hpp"
#include "Settings.hpp"
#include <ncurses.h>

#pragma mark Scene lifetime cycle

void EditorScene::OnEntrance(Window& win) {
    
    m_board = Board::CreateBoard(Settings::SharedSettings().board_type, win.GetWidth(), win.GetHeight());
    m_generation = 0;
    
    switch (Settings::SharedSettings().rules_type) {
        case Settings::Rules::kRegular: {
            
            //Order of adding the rules is very important and is following instructions
            m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
            m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
            m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
            break;
        }
        case Settings::Rules::kClassic: {
            
            m_board->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kSolitude));
            m_board->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kOverpopulation));
            m_board->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kSurvival));
            m_board->AddClassicRule(ClassicRule::CreateClassicRule(ClassicRule::Type::kPopulation));
            break;
        }
    }

    win.AddView(*m_board, 0, 0);
}

void EditorScene::OnDismiss(Window& win) {

    if (m_board) delete m_board;
}

void EditorScene::OnUpdate(Window&) {
    //Do nothing

    mvprintw(0, 0, "Generation: %i", m_generation);
    mvprintw(LINES - 1, 0, "ENTER: Increment a generation. SPACE: Reset board. F1: Return to main menu.");
}

void EditorScene::OnKeyboardEvent(Window& win, int input) {
    
    switch (input) {
            
        //Pressed Enter
        case 10: {
            
            m_board->Simulate();
            ++m_generation;
            
            break;
        }
        //Pressed Space
        case ' ': {
            
            m_board->Reset();
            m_generation = 0;
            
            break;
        }
        case KEY_F(1): {
            
            Director::SharedDirector().Present(new EntranceScene());
            break;
        }
        //Dont do anything otherwise
        default: break;
    }
}

void EditorScene::OnMouseEvent(Window& win, MEVENT event) {
    m_board->Toggle(event.x, event.y);
}
