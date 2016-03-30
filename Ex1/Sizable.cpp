//
//  Sizable.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 29/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Sizable.hpp"

Sizable::Sizable(int width, int height) :
m_width(width),
m_height(height)
{ }

int Sizable::GetHeight() const {
    return m_height;
}

int Sizable::GetWidth() const {
    return m_width;
}

void Sizable::SetWidth(int width) {
    m_width = width;
}

void Sizable::SetHeight(int height) {
    m_height = height;
}