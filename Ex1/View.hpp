//
//  View.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef View_hpp
#define View_hpp
#include "Sizable.hpp"
#include "Drawable.hpp"
#include <ncurses.h>

class View : public Sizable, public Drawable {
public:
    
    View(int width, int height);

    void Draw() const;
    virtual void Draw(WINDOW* win) const = 0;

    void SetWidth(int width);
    void SetHeight(int height);
    
    virtual ~View();

protected:
    
    virtual void Initialize(WINDOW* win);
    
private:
    
    WINDOW* m_window;
    void SetWindow(WINDOW* win);
    void RefreshWindowSize();

    friend class Window;
    
};
#endif /* View_hpp */
