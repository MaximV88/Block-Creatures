//
//  ClassicRule.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 31/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "ClassicRule.hpp"
#include "SolitudeClassicRule.hpp"

#include "Tile.hpp"

ClassicRule* ClassicRule::CreateClassicRule(ClassicRule::Type type) {
    
    switch (type) {
        case ClassicRule::Type::kSolitude: return new SolitudeClassicRule();
    }
}

ClassicRule::~ClassicRule() { }

int ClassicRule::AliveNeighbors(const Tile& marker) const {
    
    //Check all neighbors
    int alive = 0;
    
    Tile* current = marker.Neighbor(Board::Direction::kTop);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    current = marker.Neighbor(Board::Direction::kTopRight);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;

    current = marker.Neighbor(Board::Direction::kRight);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    current = marker.Neighbor(Board::Direction::kBottomRight);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    current = marker.Neighbor(Board::Direction::kBottom);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    current = marker.Neighbor(Board::Direction::kBottomLeft);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    current = marker.Neighbor(Board::Direction::kLeft);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    current = marker.Neighbor(Board::Direction::kTopLeft);
    if (current && current->CurrentState() == Tile::State::kAlive) ++alive;
    
    //Contains all alive neighbors
    return alive;
}