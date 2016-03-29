//
//  Window.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Window.hpp"
#include "View.hpp"
#include <ncurses.h>

#pragma mark - Singelnton related functions

Window& Window::SharedWindow() {
    
    static Window instance;
    instance.RefreshSize();
    
    return instance;
    
}

Window::Window() :
Sizable(0, 0) {

    //Validate that ncurses is initialize
    if (!stdscr) {
        
        initscr();
        start_color();

        init_pair(Window::Color::kRed,      COLOR_RED, COLOR_RED);
        init_pair(Window::Color::kGreen,    COLOR_GREEN, COLOR_GREEN);
        init_pair(Window::Color::kBlue,     COLOR_BLUE, COLOR_BLUE);
        init_pair(Window::Color::kMagenta,  COLOR_MAGENTA, COLOR_MAGENTA);
        init_pair(Window::Color::kBlack,    COLOR_BLACK, COLOR_BLACK);
        init_pair(Window::Color::kRedBlack, COLOR_RED, COLOR_BLACK);

    }
    
    //Startup procedures
    RefreshSize();

}

Window::~Window() {

    //Close ncurses to avoid bad behavior when exiting program
    endwin();
}

Window::Window(const Window&) :
Sizable(0, 0)
{ }

void Window::operator=(const Window &) { }

#pragma mark - Window functions

void Window::AddView(View& view, int anchor_x, int anchor_y) {
    
    view.SetWindow(newwin(view.m_height, view.m_width, anchor_y, anchor_x));
    m_subviews.push_back(view_t(&view, anchor_t(anchor_x,anchor_y)));
}

void Window::RemoveView(View& view) {
    
    //Find index of iterator that has the view
    for (std::vector<view_t>::const_iterator begin = m_subviews.begin(), end = m_subviews.end() ;
         begin != end ;
         begin++) {
        
        if (begin->first == &view) {
            m_subviews.erase(begin);
            break;
        }
    }
}

void Window::Refresh() const {
    
    for (std::vector<view_t>::const_iterator begin = m_subviews.begin(), end = m_subviews.end() ;
         begin != end ;
         begin++) {
        
        //Draw each view
        (begin->first)->Draw();
        
    }
}

void Window::RefreshSize() {
    
    //Directly refresh sizes
    getmaxyx(stdscr, m_height, m_width);
}
