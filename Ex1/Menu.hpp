//
//  Menu.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp
#include "View.hpp"
#include <string>
#include <menu.h>
#include <vector>
#include <memory>

class Menu : public View {
public:
    
    Menu(const std::string& title, int width, int height);
    ~Menu();
    
    void SetOptions(const std::vector<std::string>& options, int columns = 1);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    int CurrentIndex() const;

    void Draw(WINDOW* win) const;
    
private:
    
    void Initialize(WINDOW* win);

    class Impl;
    std::unique_ptr<Impl> m_pimpl;
    
};

#endif /* Menu_hpp */
