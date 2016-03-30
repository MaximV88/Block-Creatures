//
//  Director.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Director.hpp"
#include "Scene.hpp"
#include "Window.hpp"
#include "Listener.hpp"
#include <stdio.h>

class Director::Impl {
public:

    Impl();
    ~Impl();
    void Present(Scene *scene);
    void Run();
    
    static void HandleKeyboardEvent(int);
    static void HandleMouseEvent(MEVENT);
    
private:
    
    void UpdateEvents(Scene* scene);
    
    Scene* m_current;
    Scene* m_future;
    
    Window m_window;
    Listener m_listener;
    
    //Events that havnt been treated yet
    bool m_has_keyboard_event;
    bool m_has_mouse_event;
    
    int m_keyboard_event;
    MEVENT m_mouse_event;

};

#pragma mark - Implementation

Director::Impl::Impl() :
m_window(),
m_listener(),
m_current(NULL),
m_future(NULL),
m_has_keyboard_event(false),
m_has_mouse_event(false) {

    //Register for events
    m_listener.SetKeyboardCallback(&Director::Impl::HandleKeyboardEvent);
    m_listener.SetMouseCallback(&Director::Impl::HandleMouseEvent);
}

Director::Impl::~Impl() {
    
    //Remove any present scene
    if (m_current) delete m_current;
}

void Director::Impl::HandleMouseEvent(MEVENT event) {
    SharedDirector().m_pimpl->m_has_mouse_event = true;
    SharedDirector().m_pimpl->m_mouse_event = event;
}

void Director::Impl::HandleKeyboardEvent(int key) {
    SharedDirector().m_pimpl->m_has_keyboard_event = true;
    SharedDirector().m_pimpl->m_keyboard_event = key;
}

void Director::Impl::Present(Scene *scene) {
    
    //Checked every cycle in Run
    m_future = scene;
}

void Director::Impl::Run() {
    
    //Dont run without a scene
    if (!m_future) return;
    
    m_current = m_future;
    m_future = NULL;
    
    //Clear the previous scene from view
    m_window.Clear();
    
    m_current->OnEntrance(m_window);
    
    //While there is no new scene to show, run the current one
    while (!m_future) {
        
        //Perform updates
        m_current->OnUpdate(m_window);
        
        //Listen to events
        if (m_listener.Listen()) {
        
            //Handle events
            UpdateEvents(m_current);
        }
        
        //Show updated views
        m_window.Refresh();
        
    }
    
    //There is a new scene to show, so delete previous one
    m_current->OnDismiss(m_window);
    delete m_current;
    
    //Keep the process going
    Run();
    
}

void Director::Impl::UpdateEvents(Scene *scene) {
    
    if (m_has_keyboard_event) {
        m_has_keyboard_event = false;
        scene->OnKeyboardEvent(m_window, m_keyboard_event);
    }
    
    if (m_has_mouse_event) {
        m_has_mouse_event = false;
        scene->OnMouseEvent(m_window, m_mouse_event);
    }
}

#pragma mark - Singelnton related functions

Director& Director::SharedDirector() {
    
    static Director instance;
    return instance;

}

Director::Director() :
m_pimpl(new Impl()) { }

Director::~Director() { }

Director::Director(const Director&) { }

void Director::operator=(const Director &) { }

#pragma mark - Director functions

void Director::Present(Scene *scene) {
    m_pimpl->Present(scene);
}

void Director::Run() {
    m_pimpl->Run();
}

