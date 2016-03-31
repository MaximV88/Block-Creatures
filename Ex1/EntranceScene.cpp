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
#include "Label.hpp"
#include "Window.hpp"

//Scenes
#include "EntranceScene.hpp"
#include "AboutScene.hpp"
#include "LifeScene.hpp"
#include "EditorScene.hpp"
#include "SettingsScene.hpp"

#include "Director.hpp"
#include "Rule.hpp"
#include "CreationistRule.hpp"
#include "Settings.hpp"

#pragma mark Scene lifetime cycle

void EntranceScene::OnEntrance(Window& win) {
    
    m_background = Board::CreateBoard(Board::Type::kFlat, win.GetWidth(), win.GetHeight());
    m_background->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_background->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_background->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
    win.AddView(*m_background, 0, 0);

    //Create the scene's menu
    int menu_width = 20;
    int menu_height = 10;
    m_main_menu = new Menu("Blocky Creatures", menu_width, menu_height);
    
    std::vector<std::string> options;
    options.push_back("Play!");
    options.push_back("Editor");
    options.push_back("Settings");
    options.push_back("About");
    m_main_menu->SetOptions(options);
    
    //Add the view to the middle of the window
    win.AddView(*m_main_menu,
                (win.GetWidth() - menu_width)/ 2,
                (win.GetHeight() - menu_height) / 2);
    
    m_label = new Label("Press ENTER to choose a selection.");
    win.AddView(*m_label, 0, LINES - 1);
    
}

void EntranceScene::OnDismiss(Window& win) {
    
    if (m_background) delete m_background;
    if (m_main_menu) delete m_main_menu;
    if (m_label) delete m_label;
    
}

void EntranceScene::OnUpdate(Window& win) {
    
    //Simulate a board and animate it
    m_background->Simulate();
    usleep(150000);
}

void EntranceScene::OnKeyboardEvent(Window& win, int input) {
    
    switch (input) {
        case KEY_UP: m_main_menu->MoveUp(); break;
        case KEY_DOWN: m_main_menu->MoveDown(); break;
        case 10: {
            
            //Pressed Enter
            switch (m_main_menu->CurrentIndex()) {
                case 0: Director::SharedDirector().Present(new LifeScene());        break;
                case 1: Director::SharedDirector().Present(new EditorScene());      break;
                case 2: Director::SharedDirector().Present(new SettingsScene());    break;
                case 3: Director::SharedDirector().Present(new AboutScene());       break;
            }
            
            break;
        }
        default: break;
    }
}
