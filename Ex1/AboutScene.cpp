//
//  AboutScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "AboutScene.hpp"
#include <ncurses.h>

void AboutScene::OnEntrance(Window& win) {
    
    //Validate that ncurses is initialize
    if (!stdscr) initscr();
    
}

void AboutScene::OnDismiss(Window& win) {
    
}

void AboutScene::OnUpdate(Window& win) {
    
}

void AboutScene::OnKeyboardEvent(Window& win, int input) {
    
}