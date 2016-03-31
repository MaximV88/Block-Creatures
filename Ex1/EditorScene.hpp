//
//  EditorScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef EditorScene_hpp
#define EditorScene_hpp
#include "Scene.hpp"
class Board;

class EditorScene : public Scene {
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
    
    /**
     * Calls to inform the scene that a new event
     * from the mouse has been recieved.
     */
    void OnMouseEvent(Window&, MEVENT event);
    
private:
    
    Board* m_board;
    int m_generation;
    
};

#endif /* EditorScene_hpp */
