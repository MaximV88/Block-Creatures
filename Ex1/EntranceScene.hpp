//
//  EntranceScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef EntranceScene_hpp
#define EntranceScene_hpp
#include "Scene.hpp"
class Board;
class Menu;

class EntranceScene : public Scene {
public:
    
    /**
     * Constructor.
     */
    EntranceScene();
    
    /**
     * Destructor.
     */
    ~EntranceScene();
    
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
    void OnUpdate();
    
private:
    
    Board* m_background;
    Menu* m_main_menu;
    
};

#endif /* EntranceScene_hpp */
