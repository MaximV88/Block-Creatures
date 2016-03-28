//
//  Settings.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Settings_hpp
#define Settings_hpp
#include <stdio.h>

class Settings {
public:
    
    static Settings& SharedSettings();
    
    size_t board_width;
    size_t board_height;
    
private:
    
    Settings();
    ~Settings();
    Settings(const Settings&);
    void operator=(const Settings&);
    
};

#endif /* Settings_hpp */
