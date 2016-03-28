//
//  EntranceScene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include <ncurses.h>
#include <menu.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include "EntranceScene.hpp"
#include "AboutScene.hpp"
#include "LifeScene.hpp"
#include "EditorScene.hpp"
#include "Board.hpp"
#include "Director.hpp"
#include "Rule.hpp"
#include "CreationistRule.hpp"

struct Menu {
    MENU *menu;
    ITEM** items;
    WINDOW *window;
    std::vector<std::string> options;
    int width;
    int height;
};

void AllocateMenu(Menu&);
void DeallocateMenu(Menu&);
void AnimateLife(Board& board, int width, int height);
void PerformMenuSelection(Menu&, int);
void ReadKeyboard(Menu&);
void ScreenSize(int &width, int &height);

#pragma mark Scene lifetime cycle

EntranceScene::EntranceScene() :
m_board(Board::CreateBoard(Board::Type::kFlat, 0, 0)) {
        
    m_board->AddRule(Rule::CreateRule(Rule::Type::kStagnation));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kReversal));
    m_board->AddRule(Rule::CreateRule(Rule::Type::kRotation));
    
}

EntranceScene::~EntranceScene() {
    if (m_board) delete m_board;
}

void EntranceScene::OnEntrance() {
    
    //Validate that ncurses is initialize
    if (!stdscr) initscr();
    
    int screen_width, screen_height;
    ScreenSize(screen_width, screen_height);
    m_board->Resize(screen_width, screen_height);
    
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);

    Menu menu;
    
    menu.options.push_back("Play!");
    menu.options.push_back("Editor");
    menu.options.push_back("About");

    //Create the scene's menu
    AllocateMenu(menu);
    nodelay(stdscr, TRUE);

    //Loop the various actions
    while (true) {
        AnimateLife(*m_board, screen_width, screen_height);
        ReadKeyboard(menu);
        usleep(5000);
    }
}

void EntranceScene::OnDismiss() {
    
}

#pragma mark - Helper C functions

void PerformMenuSelection(Menu& menu, int selection_index) {
    
    //Deallocate menu items
    DeallocateMenu(menu);
    
    //Request the director to load different scenes
    switch (selection_index) {
        case 0: Director::SharedDirector().Present(new LifeScene());    break;
        case 1: Director::SharedDirector().Present(new EditorScene());  break;
        case 2: Director::SharedDirector().Present(new AboutScene());   break;
    }
    
}

void ReadKeyboard(Menu& menu) {
    
    redrawwin(menu.window);

    switch(getch()) {
            
        case KEY_DOWN:  menu_driver(menu.menu, REQ_DOWN_ITEM);    break;
        case KEY_UP:    menu_driver(menu.menu, REQ_UP_ITEM);      break;
        case 10:
            
            ITEM* selection = current_item(menu.menu);
            
            //Perform selection
            void(*handler)(Menu&, int) = (void(*)(Menu&, int))item_userptr(selection);
            handler(menu, item_index(selection));
            
            pos_menu_cursor(menu.menu);
    }
    
    wrefresh(menu.window);
}

void PrintInMiddle(WINDOW *win, int start_y, int start_x, int width, const std::string& contents, chtype color) {
    
    start_x = start_x + (int)(width - contents.length())/ 2;
    
    wattron(win, color);
    mvwprintw(win, start_y, start_x, "%s", contents.data());
    wattroff(win, color);
}

void AllocateMenu(Menu& menu) {
    
    
    int screen_size_x, screen_size_y;
    
    getmaxyx(stdscr, screen_size_y, screen_size_x);

    menu.width = 20;
    menu.height = 10;
    
    int menu_anchor_x = (screen_size_x - menu.width)/ 2;
    int menu_anchor_y = (screen_size_y - menu.height) / 2;

    //C interface demands using OS memory allocation
    menu.items = (ITEM **)calloc(menu.options.size() + 1, sizeof(ITEM *));
    
    //Fill the items with the specified options
    for(size_t index = 0; index < menu.options.size() ; index++) {
     
        menu.items[index] = new_item(menu.options[index].data(), NULL);
        
        //Set the callback
        set_item_userptr(menu.items[index], (void*)PerformMenuSelection);
    }
    
    /* Create menu */
    menu.menu = new_menu(menu.items);
    
    /* Create the window to be associated with the menu */
    menu.window = newwin(menu.height, menu.width, menu_anchor_y, menu_anchor_x);
    keypad(menu.window, TRUE);
    
    /* Set main window and sub window */
    set_menu_win(menu.menu, menu.window);
    set_menu_sub(menu.menu, derwin(menu.window, 0, 0, 4, 7));
    
    /* Set menu mark to the string " * " */
    curs_set(0);
    set_menu_mark(menu.menu, NULL);

    /* Print a border around the main window and print a title */
    box(menu.window, 0, 0);
    
    const char* title = "Blocky Creatures";
    PrintInMiddle(menu.window, 1, 0, menu.width, title, COLOR_PAIR(1));
    mvwaddch(menu.window, 2, 0, ACS_LTEE);
    mvwhline(menu.window, 2, 1, ACS_HLINE, menu.width);
    mvwaddch(menu.window, 2, 19, ACS_RTEE);

    mvprintw(LINES - 2, 1, "Created by Maxim Vainshtein and Kati Adler");
    
    /* Post the menu */
    post_menu(menu.menu);
    refresh();
}

void DeallocateMenu(Menu& menu) {
    
    unpost_menu(menu.menu);
    for(size_t index = 0 ; index < menu.options.size() ; ++index)
        free_item(menu.items[index]);
    
    free_menu(menu.menu);
    delwin(menu.window);
    free(menu.items);

}

void AnimateLife(Board& board, int width, int height) {
    
    static WINDOW* window = NULL;
    static size_t wait = 0;
    
    if (!window) window = newwin(height, width, 0, 0);
    
    if (wait++ > 100) {
        
        //Simulate a board and animate it
        board.Simulate();
        board.Draw(window, 3, 4);
        wait = 0;
        
    }
    
}

void ScreenSize(int &width, int &height) {
    getmaxyx(stdscr, height, width);
}

