//
//  Scene.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 28/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Scene.hpp"

Scene::~Scene() { }

void Scene::OnKeyboardEvent(Window& win, int input) { /* Override */ }

void Scene::OnMouseEvent(Window& win, MEVENT event) { /* Override */ }