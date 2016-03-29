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

class Menu : public View {
public:
    
    Menu(const std::string& title, int width, int height);
    ~Menu();
    
    void SetOptions(const std::vector<std::string>& options, void(*callback)(int selection_index));
    
    bool ReadInput() const;
    
    void Draw(WINDOW* win) const;
    
private:
    
    void Initialize(WINDOW *win);
    
    MENU* m_menu;
    ITEM** m_items;
    std::string m_title;
    std::vector<std::string> m_options;
    
};

#endif /* Menu_hpp */
