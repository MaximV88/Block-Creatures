//
//  CircularBoard.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef CircularBoard_hpp
#define CircularBoard_hpp
#include "Board.hpp"

class CircularBoard : public Board  {
public:

    CircularBoard(int width, int height);

    Tile* GetNeighbor(const Tile& marker, Direction direction) const;
    
};
#endif /* CircularBoard_hpp */
