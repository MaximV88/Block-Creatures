//
//  Tile.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp
#include "Board.hpp"

class Tile {
public:
    
    enum State {
        kAlive,
        kDead,
    };
    
    Tile(int pos_x, int pos_y, const Board* board, Tile::State state = Tile::State::kDead);
    
    /**
     * Toggles the state of the tile. The change is
     * NOT visible when requesting state via functions
     * as CurrentState.
     */
    void Toggle();
    
    /**
     * Updates the state of the tile. The change is
     * NOT visible when requesting state via functions
     * as CurrentState.
     *
     * @param state The state to update to.
     */
    void Update(Tile::State state);
    
    /**
     * Returns the current state.
     *
     * @return current state.
     */
    Tile::State CurrentState() const;
    
    Tile* Neighbor(Board::Direction direction) const;

    const int pos_x;
    const int pos_y;
    
private:
    
    ///Stores the state of the tile.
    Tile::State m_state;
    
    ///Stores the containing board.
    const Board& m_board;
    
    ///Stores the parallel tile.
    Tile* m_parallel;

    friend class Board;
};

#endif /* Tile_hpp */
