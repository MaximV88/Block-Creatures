//
//  SettingsScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef SettingsScene_hpp
#define SettingsScene_hpp
#include "Scene.hpp"
class Menu;
class Label;

class SettingsScene : public Scene {
public:
    
    /**
     * Calls to inform the scene that it has
     * entered into focus and can display itself.
     */
    void OnEntrance(Window&);
    
    /**
     * Calls to inform the scene that it is about
     * to leave the focus and could display any related
     * messages.
     */
    void OnDismiss(Window&);
    
    /**
     * Calls to inform the scene that it can do
     * updates to it's views.
     */
    void OnUpdate(Window&);
    
    /**
     * Calls to inform the scene that a new event
     * from the keyboard has been recieved.
     */
    void OnKeyboardEvent(Window&, int input);
    
private:
    
    void UpdateLabels();
    Menu* m_menu;
    Label* m_description;
    Label* m_current_board_type;
    Label* m_current_rules_type;
    
};

#endif /* SettingsScene_hpp */
