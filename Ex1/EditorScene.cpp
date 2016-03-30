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

EditorScene::EditorScene() :
m_board(NULL) {
    
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

void EditorScene::OnUpdate() {
    //Do nothing
}

void EditorScene::OnKeyboardEvent(int input) {
    
}

void EditorScene::OnMouseEvent(MEVENT event) {
    
}