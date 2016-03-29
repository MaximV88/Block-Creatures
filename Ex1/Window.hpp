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
        kNone = 0,
        kRed,
        kGreen,
        kBlue,
        kMagenta,
        kBlack,
        kRedBlack
    };
    
    static Window& SharedWindow();
    
    size_t height;
    size_t width;
    
    void AddView(View& view, int anchor_x, int anchor_y);
    void RemoveView(View& view);
    void Resize(const Sizable& size);
    
private:
    
    typedef std::pair<int, int> anchor_t;
    typedef std::pair<const View*, anchor_t> view_t;
    
    Window();
    ~Window();
    Window(const Window&);
    void operator=(const Window&);
    
    void Refresh() const;
    void RefreshSize();

    std::vector<view_t> m_subviews;
    
    friend class Director;
    
};

#endif /* Window_hpp */
