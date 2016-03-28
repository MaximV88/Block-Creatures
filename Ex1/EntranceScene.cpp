//
//  EntranceScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "EntranceScene.hpp"
#include <ncurses.h>
#include <menu.h>
#include <cstdlib>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void ShowTitle();
void ShowMenu();
void AnimateLife();

#pragma mark Scene lifetime cycle

void EntranceScene::OnEntrance() {
    
    //Validate that ncurses is initialize
    if (!stdscr) initscr();

    //The scene consists of several animations that constructed in the following order:
    ShowTitle();
    ShowMenu();
    AnimateLife();
    
}

void EntranceScene::OnDismiss() {
    
}

#pragma mark - Helper C functions

const char* options[] = {
    
    "Play!",
    "Settings",
    "Editor",
    "About"
    
};

void ShowTitle() {
    
}

void ShowMenu() {

    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices, i;
    ITEM *cur_item;
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    n_choices = ARRAY_SIZE(options);
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    
    for(i = 0; i < n_choices; ++i)
        my_items[i] = new_item(options[i], " 1");
    my_items[n_choices] = (ITEM *)NULL;
    
    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "F1 to Exit");
    post_menu(my_menu);
    refresh();
    
    while((c = getch()) != KEY_F(1))
    {   switch(c)
        {	case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
        }
    }
    
    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);

    
}

void AnimateLife() {
    
}