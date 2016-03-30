//
//  Listener.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 30/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Listener_hpp
#define Listener_hpp
#include <memory>
#include <ncurses.h>

class Listener {
public:
    
    Listener();
    ~Listener();
    
    /**
     * Listens to events (Mouse and Keyboard).
     *
     * @return True if catched event, false otherwise.
     */
    bool Listen() const;
    
    void SetMouseCallback(void(*callback)(MEVENT));
    void SetKeyboardCallback(void(*callback)(int));
    
private:
    
    class Impl;
    std::unique_ptr<Impl> m_pimpl;
    
};
#endif /* Listener_hpp */
