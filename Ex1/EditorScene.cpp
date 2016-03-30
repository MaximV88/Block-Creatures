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
#include "Director.hpp"
#include "EntranceScene.hpp"
#include <ncurses.h>

EditorScene::EditorScene() :
m_board(NULL),
m_generation(0) {
    
    m_board = Board::CreateBoard(Board::Type::kFlat, 0, 0);
}

EditorScene::~EditorScene() {
    if (m_board) delete m_board;
}


void EditorScene::OnEntrance(Window& win) {
    
    m_board->Resize(win);
    
    //Order of adding the rules is very important and is following instructions
    m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    win.AddView(*m_board, 0, 0);
}

void EditorScene::OnDismiss(Window& win) {

}

void EditorScene::OnUpdate(Window&) {
    //Do nothing

    mvprintw(0, 0, "Generation: %i", m_generation);
    mvprintw(LINES - 1, 0, "ENTER: Increment a generation. F1: Return to main menu.");
}

void EditorScene::OnKeyboardEvent(Window& win, int input) {
    
    switch (input) {
            
        //Pressed Enter
        case 10: {
            
            m_board->Simulate();
            ++m_generation;
            
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
    m_board->Highlight(event.x, event.y);
}