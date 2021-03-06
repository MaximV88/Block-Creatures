//
//  Scene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp
#include <ncurses.h>
class Window;

class Scene {
public:
    
    /**
     * Calls to inform the scene that it has
     * entered into focus and can display itself.
     */
    virtual void OnEntrance(Window&) = 0;
    
    /**
     * Calls to inform the scene that it is about
     * to leave the focus and could display any related
     * messages.
     */
    virtual void OnDismiss(Window&) = 0;
    
    /**
     * Calls to inform the scene that it can do
     * updates to it's views.
     */
    virtual void OnUpdate(Window&) = 0;
    
    /**
     * Calls to inform the scene that a new event
     * from the keyboard has been recieved.
     */
    virtual void OnKeyboardEvent(Window&, int input);
    
    /**
     * Calls to inform the scene that a new event
     * from the mouse has been recieved.
     */
    virtual void OnMouseEvent(Window&, MEVENT event);
    
    /**
     * Destructor.
     */
    virtual ~Scene();
    
};
#endif /* Scene_hpp */
