//
//  Game.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include "Board.hpp"

class Game {
public:
    
    Game();
    ~Game();
    
private:
    
    Board* m_board;
    
};
#endif /* Game_hpp */
