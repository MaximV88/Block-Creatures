//
//  Window.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp
#include "Sizable.hpp"
#include <stdio.h>
#include <vector>

class View;

class Window : public Sizable {
public:
    
    enum Color {
        kRed = 1,
        kGreen,
        kBlue,
        kRedBlack
    };
    
    static Window& SharedWindow();
    
    size_t height;
    size_t width;
    
    void AddView(View& view, int anchor_x, int anchor_y);
    void RemoveView(View& view);

private:
    
    Window();
    ~Window();
    Window(const Window&);
    void operator=(const Window&);
    
    void RefreshSize();

    std::vector<const View*> m_subviews;
    
};

#endif /* Window_hpp */
