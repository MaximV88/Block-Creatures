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


class Menu::Impl {
public:
    
    Impl(const std::string& title, Menu& menu);
    ~Impl();
    
    void SetOptions(const std::vector<std::string>& options, void(*callback)(int selection_index));
    int CurrentIndex() const;
    void MoveUp();
    void MoveDown();
    
    void Draw(WINDOW* win) const;
    void Initialize(WINDOW *win);

private:
    
    MENU* m_menu;
    ITEM** m_items;
    std::string m_title;
    std::vector<std::string> m_options;
    
    //Required for inheritance accessors
    Menu& m_owner;
    
};

void PrintInMiddle(WINDOW *win, int start_y, int start_x, int width, const std::string& contents, chtype color);

Menu::Impl::Impl(const std::string& title, Menu& menu) :
m_owner(menu),
m_title(title) {
    
}

Menu::Impl::~Impl() {
    
    if (m_menu) unpost_menu(m_menu);
    
    if (m_items) {
        
        for(size_t index = 0 ; index < m_options.size() ; ++index)
            free_item(m_items[index]);
        
        if (m_menu) free_menu(m_menu);
        free(m_items);
        
    }
    
}

int Menu::Impl::CurrentIndex() const {
    
    pos_menu_cursor(m_menu);
    return item_index(current_item(m_menu));
}

void Menu::Impl::MoveUp() {
    menu_driver(m_menu, REQ_UP_ITEM);
}

void Menu::Impl::MoveDown() {
    menu_driver(m_menu, REQ_DOWN_ITEM);
}

void Menu::Impl::Initialize(WINDOW *win) {

    /* Set main window and sub window */
    set_menu_win(m_menu, win);
    set_menu_sub(m_menu, derwin(win, 0, 0, 4, 7));
    
    /* Set menu mark to the string " " */
    curs_set(0);
    set_menu_mark(m_menu, NULL);
    
    /* Print a border around the main window and print a title */
    box(win, 0, 0);
    
    PrintInMiddle(win, 1, 0, m_owner.GetWidth(), m_title, COLOR_PAIR(Window::Color::kRedBlack));

    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, m_owner.GetWidth());
    mvwaddch(win, 2, m_owner.GetWidth() - 1, ACS_RTEE);
    
    /* Post the menu */
    post_menu(m_menu);
}

void Menu::Impl::SetOptions(const std::vector<std::string>& options, void(*callback)(int selection_index)) {
    
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

void Menu::Impl::Draw(WINDOW *win) const {
    
    //A more complete implementation would have this in the Window class, but time is short
    redrawwin(win);

}

void PrintInMiddle(WINDOW *win, int start_y, int start_x, int width, const std::string& contents, chtype color) {
    
    start_x = start_x + (int)(width - contents.length())/ 2;
    
    wattron(win, color);
    mvwprintw(win, start_y, start_x, "%s", contents.data());
    wattroff(win, color);
}

#pragma mark - Menu methods

Menu::Menu(const std::string& title, int width, int height) :
View(width, height),
m_pimpl(new Impl(title, *this))
{ }

Menu::~Menu() { }

void Menu::SetOptions(const std::vector<std::string> &options, void (*callback)(int)) {
    m_pimpl->SetOptions(options, callback);
}

int Menu::CurrentIndex() const {
    return m_pimpl->CurrentIndex();
}

void Menu::MoveUp() {
    m_pimpl->MoveUp();
}

void Menu::MoveDown() {
    m_pimpl->MoveDown();
}

void Menu::Initialize(WINDOW *win) {
    m_pimpl->Initialize(win);
}

void Menu::Draw(WINDOW *win) const {
    m_pimpl->Draw(win);
}
