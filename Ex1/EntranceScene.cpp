//
//  EntranceScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include <ncurses.h>
#include <menu.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

//GUI
#include "Menu.hpp"
#include "Board.hpp"
#include "Window.hpp"

#include "EntranceScene.hpp"
#include "AboutScene.hpp"
#include "LifeScene.hpp"
#include "EditorScene.hpp"
#include "Director.hpp"
#include "Rule.hpp"
#include "CreationistRule.hpp"

//Callback handler for menu selection
void MenuSelection(int selection_index);

#pragma mark Scene lifetime cycle

EntranceScene::EntranceScene() :
m_background(Board::CreateBoard(Board::Type::kFlat, 0, 0)) {
        
    m_background->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_background->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_background->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
}

EntranceScene::~EntranceScene() {
    if (m_background) delete m_background;
    if (m_main_menu) delete m_main_menu;
}

void EntranceScene::OnEntrance(Window& win) {
    
    m_background->Resize(win);
    win.AddView(*m_background, 0, 0);

    //Create the scene's menu
    int menu_width = 20;
    int menu_height = 10;
    m_main_menu = new Menu("Blocky Creatures", menu_width, menu_height);
    
    std::vector<std::string> options;
    options.push_back("Play!");
    options.push_back("Editor");
    options.push_back("About");
    m_main_menu->SetOptions(options, MenuSelection);
    
    //Add the view to the middle of the window
    win.AddView(*m_main_menu,
                (win.GetWidth() - menu_width)/ 2,
                (win.GetHeight() - menu_height) / 2);
    
}

void EntranceScene::OnDismiss(Window& win) {
    
    win.RemoveView(*m_background);
    win.RemoveView(*m_main_menu);
    
}

void EntranceScene::OnUpdate() {
    
    
        //Simulate a board and animate it
        m_background->Simulate();
        
    
    //Try to read possible input
    m_main_menu->ReadInput();
    mvprintw(LINES - 1, 0, "Created by Maxim Vainshtein and Kati Adler");

    usleep(150000);
}

#pragma mark - Helper C functions

void MenuSelection(int selection_index) {

    //Request the director to load different scenes
    switch (selection_index) {
        case 0: Director::SharedDirector().Present(new LifeScene());    break;
        case 1: Director::SharedDirector().Present(new EditorScene());  break;
        case 2: Director::SharedDirector().Present(new AboutScene());   break;
    }
}
