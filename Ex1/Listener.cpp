//
//  Listener.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 30/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Listener.hpp"

class Listener::Impl {
public:
    
    Impl();
    bool Listen() const;
    
    void SetMouseCallback(void(*)(MEVENT));
    void SetKeyboardCallback(void(*)(int));
    
private:
    
    void(*m_mouse_callback)(MEVENT);
    void(*m_keyboard_callback)(int);
    
};

#pragma mark - Implementation

Listener::Impl::Impl() :
m_mouse_callback(NULL),
m_keyboard_callback(NULL) {

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

}

bool Listener::Impl::Listen() const {
    
    int key = getch();
    
    switch(key) {
        case KEY_MOUSE: {
            
            MEVENT mouse_event;
            if(getmouse(&mouse_event) == OK) {
                
                //Call the callback
                if (m_mouse_callback)
                    m_mouse_callback(mouse_event);
                
                return true;
            }
            break;
        }
        default: {
            
            if (m_keyboard_callback) {
                m_keyboard_callback(key);
            }
            
            return true;
        }
    }
    
    return false;
}

void Listener::Impl::SetMouseCallback(void (*callback)(MEVENT)) {
    m_mouse_callback = callback;
}

void Listener::Impl::SetKeyboardCallback(void (*callback)(int)) {
    m_keyboard_callback = callback;
}

#pragma mark - Listener methods

Listener::Listener() :
m_pimpl(new Impl())
{ }

Listener::~Listener() { }

void Listener::SetMouseCallback(void (*callback)(MEVENT)) {
    m_pimpl->SetMouseCallback(callback);
}

void Listener::SetKeyboardCallback(void (*callback)(int)) {
    m_pimpl->SetKeyboardCallback(callback);
}

bool Listener::Listen() const {
    return m_pimpl->Listen();
}
