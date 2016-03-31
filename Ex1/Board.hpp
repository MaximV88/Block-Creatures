//
//  Board.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 27/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp
#include "View.hpp"
#include <vector>
#include <ncurses.h>
#include <iostream>
#include <memory>
class Tile;
class Rule;
class ClassicRule;

/**
 * The Board holds Tile objects, and is responsible for
 * returning blocks and tiles according to direction.
 * <br>
 * The coordinate system is structured by having (0,0) for the upper left corner.
 */
class Board : public View {
public:
    
    /**
     * Possible directions for each tile to 
     * reference another tile.
     */
    enum Direction {
        kTop,
        kBottom,
        kLeft,
        kRight,
        kTopRight,
        kTopLeft,
        kBottomRight,
        kBottomLeft
    };
    
    /**
     * Board behavior types.
     */
    enum Type {
        kFlat,
        kCircular
    };
    
    /**
     * Represents a block as the excercise states.
     */
    struct Block {
        Tile* top_left;
        Tile* top_right;
        Tile* bottom_left;
        Tile* bottom_right;
    };
    
    /**
     * Returns a heap allocated board of specified type.
     *
     * @param type The type of board to create.
     * @return Heap allocated board.
     */
    static Board* CreateBoard(Board::Type type, int width, int height);
    
    /**
     * Destructor.
     */
    virtual ~Board();
    
    /**
     * Returns neighbor of the input tile at the requested direction.
     * Does not gurantee that a tile does exist and may return NULL.
     *
     * @param marker The tile to have it's neighbor returned.
     * @param direction The neighbor's direction from the input tile.
     * @return Neighbor tile that is located at the input direction from input tile.
     */
    virtual Tile* GetNeighbor(const Tile& marker, Direction direction) const = 0;
    
    /**
     * Returns a block that the input tile is part of.
     *
     * @param marker The tile to have it's block returned.
     * @return Block that contains the input tile inside, among other tiles.
     */
    virtual Block GetBlock(const Tile& marker) const;
    
    /**
     * Adds a rule to be applied at simulation.
     * They are later applied in the order which they
     * were added.
     *
     * @param rule The rule to add.
     */
    void AddRule(Rule* rule);
    
    /**
     * Adds a classic rule to be applied at simulation.
     * They are later applied in the order which they
     * were added.
     *
     * @param rule The classic rule to add.
     */
    void AddClassicRule(ClassicRule* rule);

    /**
     * Clears all of the stored rules in the board,
     * both classic and regular.
     */
    void ClearRules();
    
    /**
     * Performs the stores rules on the board.
     * Classic rules are performed before reguler
     * ones.
     */
    void Simulate();
    
    /**
     * Resets the board to have all of it's tile set
     * to starting state.
     */
    void Reset();
    
    /**
     * Resizes the board to input size.
     *
     * @param size The size to resize the board to.
     */
    void Resize(const Sizable& size);
    
    /**
     * Toggles the tile state at the input coordinates.
     *
     * @param pos_x X position of tile.
     * @param pos_y Y position of tile.
     */
    void Toggle(int pos_x, int pos_y);
    
    /**
     * Draws contents of the Board into a WINDOW object
     * given by ncurses library.
     *
     * @param win The window to draw into.
     */
    void Draw(WINDOW* win) const;
    
    /**
     * Prints out layout of the board into the terminal. 
     * Debug purposes when ncurses is not available.
     */
    friend std::ostream& operator<<(std::ostream& out, const Board& board);

protected:
    
    /**
     * Constructor.
     *
     * @param width The width the board should have.
     * @param height The height the board should have.
     */
    Board(int width, int height);
    
    /**
     * Returns the tile at the specified location.
     * If no tile exists, returns NULL.
     *
     * @param pos_x The X location of the requested tile.
     * @param pos_y The Y location of the requested tile.
     * @return The tile that is stored in the board. May return NULL.
     */
    Tile* GetTile(int pos_x, int pos_y) const;
    
private:
    
    class Impl;
    std::unique_ptr<Impl> m_pimpl;
    
};

#endif /* Board_hpp */
