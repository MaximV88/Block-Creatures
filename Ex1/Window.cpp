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
    m_subviews.push_back(&view);  
}

void Window::RemoveView(View& view) {
    
}

void Window::RefreshSize() {
    
    //Directly refresh sizes
    getmaxyx(stdscr, m_height, m_width);
}
