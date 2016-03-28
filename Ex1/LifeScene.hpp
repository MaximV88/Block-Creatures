//
//  LifeScene.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef LifeScene_hpp
#define LifeScene_hpp
#include "Scene.hpp"
class Board;

class LifeScene : public Scene {
public:
    
    /**
     * Constructor.
     */
    LifeScene();
    
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
    
private:
    
    Board* m_board;
    
};

#endif /* LifeScene_hpp */
