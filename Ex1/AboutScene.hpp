//
//  AboutScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef AboutScene_hpp
#define AboutScene_hpp
#include "Scene.hpp"

class AboutScene : public Scene {
public:
    
    /**
     * Calls to inform the scene that it has
     * entered into focus and can display itself.
     */
    void OnEntrance();
    
    /**
     * Calls to inform the scene that it is about
     * to leave the focus and could display any related
     * messages.
     */
    void OnDismiss();
    
};

#endif /* AboutScene_hpp */
