//
//  Drawable.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp
#include <ncurses.h>

class Drawable {
public:
    
    virtual void Draw(WINDOW* win) const = 0;
    
};
#endif /* Drawable_hpp */
