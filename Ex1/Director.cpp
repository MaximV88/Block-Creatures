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

class Director::Impl {
public:

    Impl();
    ~Impl();
    void Present(Scene *scene);
    void Run();
    
private:
    
    Scene* m_current;
    Scene* m_future;
    
    Window m_window;

};

#pragma mark - Implementation

Director::Impl::Impl() :
m_current(NULL),
m_future(NULL) {
    
}

Director::Impl::~Impl() {
    
    //Remove any present scene
    if (m_current) delete m_current;
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
        
        m_current->OnUpdate();
        m_window.Refresh();
        
    }
    
    //There is a new scene to show, so delete previous one
    m_current->OnDismiss(m_window);
    delete m_current;
    
    //Keep the process going
    Run();
    
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

