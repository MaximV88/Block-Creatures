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

class CircularBoard : Board  {
public:

    CircularBoard(size_t width, size_t height);

    virtual Tile* GetNeighbor(const Tile& marker, Direction direction) const = 0;
    
};
#endif /* CircularBoard_hpp */
