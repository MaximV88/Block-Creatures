//
//  SettingsScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "SettingsScene.hpp"

//GUI
#include "Menu.hpp"
#include "Label.hpp"
#include "Window.hpp"

//Scenes
#include "EntranceScene.hpp"

#include "Director.hpp"
#include "Settings.hpp"

#pragma mark Scene lifetime cycle

void SettingsScene::OnEntrance(Window& win) {
    
    //Create the scene's menu
    int menu_width = 37;
    int menu_height = 10;
    m_menu = new Menu("Settings", menu_width, menu_height);
    
    std::vector<std::string> options;
    
    //Type of board
    options.push_back("Wrapped board");
    options.push_back("Flat board");
    
    //Type of rules
    options.push_back("Exercise rules");
    options.push_back("Classic rules");
    
    //Create a menu with 2 columns
    m_menu->SetOptions(options, 2);

    
    //Add the view to the middle of the window
    win.AddView(*m_menu,
                (win.GetWidth() - menu_width)/ 2,
                (win.GetHeight() - menu_height) / 2);
    
    m_description = new Label("Enter: Set selection. Q: Return to main menu.");
    win.AddView(*m_description, 0, LINES - 1);
    
    m_current_board_type = new Label("Board Type: ");
    win.AddView(*m_current_board_type, 0, 0);
    
    m_current_rules_type = new Label("Rules Type: ");
    win.AddView(*m_current_rules_type, 0, 1);
    
    UpdateLabels();
}

void SettingsScene::OnDismiss(Window& win) {
    if (m_menu) delete m_menu;
    if (m_description) delete m_description;
    if (m_current_board_type) delete m_current_board_type;
    if (m_current_rules_type) delete m_current_rules_type;
}

void SettingsScene::OnUpdate(Window& win) {
    
}

void SettingsScene::OnKeyboardEvent(Window& win, int input) {
    
    switch (input) {
        case KEY_UP:    m_menu->MoveUp();      break;
        case KEY_DOWN:  m_menu->MoveDown();  break;
        case KEY_LEFT:  m_menu->MoveLeft();  break;
        case KEY_RIGHT: m_menu->MoveRight(); break;
        case 'q': {
            
            Director::SharedDirector().Present(new EntranceScene());
            break;
        }
        case 10: {
            
            //Pressed Enter
            switch (m_menu->CurrentIndex()) {
                case 0: {
                    
                    Settings::SharedSettings().board_type = Board::Type::kCircular;
                    UpdateLabels();
                    break;
                }
                case 1: {
                 
                    Settings::SharedSettings().board_type = Board::Type::kFlat;
                    UpdateLabels();
                    break;
                }
                case 2: {
                    
                    Settings::SharedSettings().rules_type = Settings::Rules::kRegular;
                    UpdateLabels();
                    break;
                }
                case 3: {
                    
                    Settings::SharedSettings().rules_type = Settings::Rules::kClassic;
                    UpdateLabels();
                    break;
                }
            }
            break;
        }
    }
}

void SettingsScene::UpdateLabels() {
    
    //Remove previous characters
    clear();
    
    switch (Settings::SharedSettings().board_type) {
        case Board::Type::kCircular:    m_current_board_type->Update("Board Type: Wrapped"); break;
        case Board::Type::kFlat:        m_current_board_type->Update("Board Type: Flat"); break;
    }
    
    switch (Settings::SharedSettings().rules_type) {
        case Settings::Rules::kRegular: m_current_rules_type->Update("Rules Type: Exercise"); break;
        case Settings::Rules::kClassic: m_current_rules_type->Update("Rules Type: Classic"); break;
    }
}
