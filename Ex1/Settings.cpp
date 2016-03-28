//
//  Settings.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Settings.hpp"

#pragma mark - Singelnton related functions

Settings& Settings::SharedSettings() {
    
    static Settings instance;
    return instance;
    
}

Settings::Settings() { }

Settings::~Settings() { }

Settings::Settings(const Settings&) { }

void Settings::operator=(const Settings &) { }

#pragma mark - Settings functions