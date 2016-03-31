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
    
    Impl(Menu& menu, const std::string& title);
    ~Impl();
    
    void SetOptions(const std::vector<std::string>& options, int columns);
    int CurrentIndex() const;
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    
    void Draw(WINDOW* win) const;
    void Initialize(WINDOW *win);

private:
    
    MENU* m_menu;
    ITEM** m_items;
    std::string m_title;
    std::vector<std::string> m_options;
    int m_columns;
    
    //Required for inheritance accessors
    Menu& m_owner;
    
};

void PrintInMiddle(WINDOW *win, int start_y, int start_x, int width, const std::string& contents, chtype color);

Menu::Impl::Impl(Menu& menu, const std::string& title) :
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

void Menu::Impl::MoveLeft() {
    menu_driver(m_menu, REQ_LEFT_ITEM);
}

void Menu::Impl::MoveRight() {
    menu_driver(m_menu, REQ_RIGHT_ITEM);
}

void Menu::Impl::Initialize(WINDOW *win) {

    //Find longest option
    size_t longest = 0;
    size_t longest_row = 0;
    size_t index = 0;
    for (size_t column = 0 ; column < m_options.size() / m_columns ; column++) {
        for (std::vector<std::string>::const_iterator begin = m_options.begin(), end = m_options.begin() + m_columns ;
             begin != end ;
             begin++, ++index) {
         
            longest += (*begin).length();
            
        }
        
        if (longest_row < longest)
            longest_row = longest;
        
        longest = 0;
    }

    /* Set main window and sub window */
    set_menu_win(m_menu, win);
    set_menu_sub(m_menu, derwin(win, 0, 0, 4, (int)((m_owner.GetWidth() - longest_row) / 2) - m_columns));
    
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

void Menu::Impl::SetOptions(const std::vector<std::string>& options, int columns) {
    
    m_items = (ITEM **)calloc(options.size() + 1, sizeof(ITEM *));
    m_options = options;
    
    //Create and set callback for each option
    for(size_t index = 0; index < m_options.size() ; index++) {
        
        m_items[index] = new_item(m_options[index].data(), NULL);
        
    }
    
    //Create ncurses menu
    m_menu = new_menu(m_items);
    
    //Set number of columns
    m_columns = columns;
    set_menu_format(m_menu, 5, m_columns);

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
m_pimpl(new Impl(*this, title))
{ }

Menu::~Menu() { }

void Menu::SetOptions(const std::vector<std::string> &options, int columns) {
    m_pimpl->SetOptions(options, columns);
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

void Menu::MoveLeft() {
    m_pimpl->MoveLeft();
}

void Menu::MoveRight() {
    m_pimpl->MoveRight();
}

void Menu::Initialize(WINDOW *win) {
    m_pimpl->Initialize(win);
}

void Menu::Draw(WINDOW *win) const {
    m_pimpl->Draw(win);
}
