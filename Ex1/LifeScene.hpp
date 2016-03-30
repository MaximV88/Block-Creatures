//
//  LifeScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef LifeScene_hpp
#define LifeScene_hpp
#include "Scene.hpp"
class Board;
class Label;

class LifeScene : public Scene {
public:
    
    /**
     * Constructor.
     */
    LifeScene();
    
    /**
     * Destructor.
     */
    ~LifeScene();
    
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
    
    Board* m_board;
    Label* m_label;
    int m_generation;
    
    
};

#endif /* LifeScene_hpp */
