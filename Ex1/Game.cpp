//
//  Game.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Game.hpp"
#include "Director.hpp"
#include "EntranceScene.hpp"

Game::Game() {
    
    //Show the entrance scene
    Director::SharedDirector().Present(new EntranceScene());
    
}

Game::~Game() {
    
    
}