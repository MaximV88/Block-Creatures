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
#include <stdio.h>

#pragma mark - Singelnton related functions

Director& Director::SharedDirector() {
    
    static Director instance;
    return instance;

}

Director::Director() :
m_current(NULL),
m_future(NULL)
{ }

Director::~Director() {
    
    //Remove any present scene
    if (m_current) delete m_current;
}

Director::Director(const Director&) { }

void Director::operator=(const Director &) { }

#pragma mark - Director functions

void Director::Present(Scene *scene) {
    
    //Checked every cycle in Run
    m_future = scene;
}

void Director::Run() {
    
    //Dont run without a scene
    if (!m_future) return;
    
    Window& win = Window::SharedWindow();
    
    m_current = m_future;
    m_future = NULL;
    
    m_current->OnEntrance(win);

    //While there is no new scene to show, run the current one
    while (!m_future) {
        
        m_current->OnUpdate();
        win.Refresh();
        
    }

    //There is a new scene to show, so delete previous one
    m_current->OnDismiss(win);
    delete m_current;
    
    //Keep the process going
    Run();
    
}
