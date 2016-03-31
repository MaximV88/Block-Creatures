//
//  Label.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 30/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp
#include "View.hpp"
#include <string>
#include <memory>

class Label : public View {
public:
    
    Label(const std::string& content);
    ~Label();
    
    void Draw(WINDOW* win) const;
    void Update(const std::string& content);

private:
    
    class Impl;
    std::unique_ptr<Impl> m_pimpl;
    
};
#endif /* Label_hpp */
