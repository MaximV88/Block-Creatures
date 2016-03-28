//
//  FlatBoard.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef FlatBoard_hpp
#define FlatBoard_hpp
#include "Board.hpp"

class FlatBoard : public Board {
public:

    FlatBoard(size_t width, size_t height);
    
    Tile* GetNeighbor(const Tile& marker, Direction direction) const;
    
};

#endif /* FlatBoard_hpp */
