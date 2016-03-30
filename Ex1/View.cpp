//
//  View.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "View.hpp"
#include "Board.hpp"
#include "Menu.hpp"

View::View(int width, int height) :
Sizable(width, height)
{ }

View::~View() {
    
    if (m_window) delwin(m_window);
}

void View::Draw() const {
    
    //Submethods dont expect a nil value
    if (m_window) {
        
        keypad(m_window, TRUE);
        Draw(m_window);
        wrefresh(m_window);
    }
}

void View::Initialize(WINDOW *win) { /* Override function */ }

void View::SetWindow(WINDOW *win) {
    
    m_window = win;
    Initialize(win);
    
}