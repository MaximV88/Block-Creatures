//
//  EditorScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "EditorScene.hpp"
#include <ncurses.h>

void EditorScene::OnEntrance() {
    
    //Validate that ncurses is initialize
    if (!stdscr) initscr();
    
}

void EditorScene::OnDismiss() {
    
}