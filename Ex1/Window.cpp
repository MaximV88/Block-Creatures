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
#include <vector>

class Window::Impl {
public:
    
    typedef std::pair<int, int> anchor_t;
    typedef std::pair<const View*, anchor_t> view_t;
    
    Impl();
    ~Impl();
    
    void AddView(View& view, int anchor_x, int anchor_y);
    void RefreshSize();
    void Clear();
    
    void Refresh() const;
    void HandleResize();
    
    static void ResizeHandler(int);
    
    std::vector<view_t> m_subviews;
    
};

#pragma mark - Implementation

Window::Impl::Impl() {
    
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
    
}

Window::Impl::~Impl() {
    
    //Close ncurses to avoid bad behavior when exiting program
    endwin();
}

void Window::Impl::Refresh() const {
    
    for (std::vector<view_t>::const_iterator begin = m_subviews.begin(), end = m_subviews.end() ;
         begin != end ;
         begin++) {
        
        //Draw each view
        (begin->first)->Draw();
        
    }
}

void Window::Impl::AddView(View &view, int anchor_x, int anchor_y) {
    
    view.SetWindow(newwin(view.GetHeight(), view.GetWidth(), anchor_y, anchor_x));
    m_subviews.push_back(view_t(&view, anchor_t(anchor_x,anchor_y)));
}

void Window::Impl::Clear() {
    
    clear();
    refresh();
    
    //Clear all subviews
    m_subviews.clear();
}

#pragma mark - Singelnton related functions

Window::Window() :
Sizable(0, 0),
m_pimpl(new Impl()) {
    
    //Startup procedures
    RefreshSize();

}

Window::Window(const Window&) :
Sizable(0, 0)
{ }

void Window::operator=(const Window &) { }

Window::~Window() { }

#pragma mark - Window functions

void Window::AddView(View& view, int anchor_x, int anchor_y) {
    m_pimpl->AddView(view, anchor_x, anchor_y);
}

void Window::RefreshSize() {
    
    int new_height, new_width;
    
    //Directly refresh sizes
    getmaxyx(stdscr, new_height, new_width);
    
    if (new_height != GetHeight() ||
        new_width != GetWidth()) {
        
        //Notify handler -> Director?
        
    }
    
    //Update new size
    SetHeight(new_height);
    SetWidth(new_width);
}

void Window::Refresh() const {
    m_pimpl->Refresh();
}

void Window::Clear() {
    m_pimpl->Clear();
}
