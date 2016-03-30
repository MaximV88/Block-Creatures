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
#include <memory>

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
    
    void AddView(View& view, int anchor_x, int anchor_y);
    void RemoveView(View& view);
    void RefreshSize();
    void Clear();
        
private:
    
    Window();
    ~Window();
    Window(const Window&);
    void operator=(const Window&);
    
    void Refresh() const;

    class Impl;
    std::unique_ptr<Impl> m_pimpl;
    
    friend class Director;
    
};

#endif /* Window_hpp */
