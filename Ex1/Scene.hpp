//
//  Scene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp
class Window;

class Scene {
public:
    
    /**
     * Calls to inform the scene that it has
     * entered into focus and can display itself.
     */
    virtual void OnEntrance(Window&) = 0;
    
    /**
     * Calls to inform the scene that it is about
     * to leave the focus and could display any related
     * messages.
     */
    virtual void OnDismiss(Window&) = 0;
    
    virtual void OnUpdate() = 0;
    
  //  virtual void OnResize(Window&) = 0;
   
    
    /**
     * Destructor.
     */
    virtual ~Scene();
    
};
#endif /* Scene_hpp */
