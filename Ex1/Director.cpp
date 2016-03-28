//
//  Director.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Director.hpp"
#include "Scene.hpp"
#include <stdio.h>

#pragma mark - Singelnton related functions

Director& Director::SharedDirector() {
    
    static Director instance;
    return instance;

}

Director::Director() :
m_current(NULL)
{ }

Director::~Director() {
    
    //Remove any present scene
    if (m_current) delete m_current;
    
}

Director::Director(const Director&) { }

void Director::operator=(const Director &) { }

#pragma mark - Director functions

void Director::Present(Scene *scene) {
    
    //Remove the previous scene
    if (m_current) {
     
        m_current->OnDismiss();
        delete m_current;
        
    }
    
    //Show the new one
    m_current = scene;
    m_current->OnEntrance();
    
}