//
//  Menu.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Menu.hpp"
#include "Window.hpp"
#include <stdlib.h>

void PrintInMiddle(WINDOW *win, int start_y, int start_x, int width, const std::string& contents, chtype color);

Menu::Menu(const std::string& title, int width, int height) :
View(width, height),
m_title(title) {
    
}

Menu::~Menu() {
    
    if (m_menu) unpost_menu(m_menu);
    
    if (m_items) {
        
        for(size_t index = 0 ; index < m_options.size() ; ++index)
            free_item(m_items[index]);
        
        if (m_menu) free_menu(m_menu);
        free(m_items);
        
    }
}

void Menu::Initialize(WINDOW *win) {
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    /* Set main window and sub window */
    set_menu_win(m_menu, win);
    set_menu_sub(m_menu, derwin(win, 0, 0, 4, 7));
    
    /* Set menu mark to the string " " */
    curs_set(0);
    set_menu_mark(m_menu, NULL);
    
    /* Print a border around the main window and print a title */
    box(win, 0, 0);
    
    PrintInMiddle(win, 1, 0, m_width, m_title, COLOR_PAIR(Window::Color::kRedBlack));

    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, m_width);
    mvwaddch(win, 2, 19, ACS_RTEE);
    
    /* Post the menu */
    post_menu(m_menu);
}

void Menu::SetOptions(const std::vector<std::string>& options, void(*callback)(int selection_index)) {
    
    m_items = (ITEM **)calloc(options.size() + 1, sizeof(ITEM *));
    m_options = options;
    
    //Create and set callback for each option
    for(size_t index = 0; index < m_options.size() ; index++) {
        
        m_items[index] = new_item(m_options[index].data(), NULL);
        set_item_userptr(m_items[index], (void*)callback);
        
    }
    
    //Create ncurses menu
    m_menu = new_menu(m_items);
}

bool Menu::ReadInput() const {
    
    switch(getch()) {
            
        case KEY_DOWN:  menu_driver(m_menu, REQ_DOWN_ITEM);    break;
        case KEY_UP:    menu_driver(m_menu, REQ_UP_ITEM);      break;
        case 10:
            
            ITEM* selection = current_item(m_menu);
            
            //Perform selection
            void(*callback)(int) = (void(*)(int))item_userptr(selection);
            callback(item_index(selection));
            
            pos_menu_cursor(m_menu);
            return true;
    }
    
    return false;
}

void Menu::Draw(WINDOW *win) const {
    
    //A more complete implementation would have this in the Window class, but time is short
    redrawwin(win);

}

void PrintInMiddle(WINDOW *win, int start_y, int start_x, int width, const std::string& contents, chtype color) {
    
    start_x = start_x + (int)(width - contents.length())/ 2;
    
    wattron(win, color);
    mvwprintw(win, start_y, start_x, "%s", contents.data());
    wattroff(win, color);
}
