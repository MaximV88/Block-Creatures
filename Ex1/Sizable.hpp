//
//  Sizable.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Sizable_hpp
#define Sizable_hpp

class Sizable {
public:
    
    Sizable(int width, int height);
    
    int GetWidth() const;
    int GetHeight() const;
    
protected:
    
    int m_width;
    int m_height;
    
};

#endif /* Sizable_hpp */
