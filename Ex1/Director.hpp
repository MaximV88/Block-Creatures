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
    
    /**
     * Requests the director to present
     * a new scene once possible.
     *
     * @param scene The scene to present.
     */
    void Present(Scene *scene);

    /**
     * Takes the future scene to be the current scene
     * with all procedure such as OnEntrance handled by
     * logical order.
     */
    void Run();
    
private:
    
    Director();
    ~Director();
    Director(const Director&);
    void operator=(const Director&);
    
    Scene* m_current;
    Scene* m_future;
    
};

#endif /* Director_hpp */
