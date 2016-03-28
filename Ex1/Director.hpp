//
//  Director.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Director_hpp
#define Director_hpp
class Scene;

class Director {
public:

    static Director& SharedDirector();
    
    void Present(Scene *scene);

private:
    
    Director();
    ~Director();
    Director(const Director&);
    void operator=(const Director&);
    
    Scene* m_current;
    
};

#endif /* Director_hpp */
