//
//  AboutScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef AboutScene_hpp
#define AboutScene_hpp
#include "Scene.hpp"
class Board;
class Label;

class AboutScene : public Scene {
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
    
    Board* m_top_left;
    Board* m_top_right;
    Board* m_bottom_left;
    Board* m_bottom_right;
    Label* m_about;
    Label* m_instructions;
    
    void RandomizeBoardPopulation(Board*);
    
};

#endif /* AboutScene_hpp */
