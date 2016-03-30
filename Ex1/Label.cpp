//
//  Label.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 30/03/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Label.hpp"

class Label::Impl {
public:
    
    Impl(Label& owner, const std::string& content);
    void Update(const std::string& content);

    void Draw(WINDOW* win) const;

    void Initialize(WINDOW* win);
    
private:
    
    std::string m_content;
    
    //Required for inheritance accessors
    Label& m_owner;
    
};

#pragma mark - Implementation

Label::Impl::Impl(Label& owner, const std::string& content) :
m_owner(owner),
m_content(content)
{ }

void Label::Impl::Update(const std::string &content) {
    m_content = content;
}

void Label::Impl::Draw(WINDOW *win) const {
    mvwprintw(win, 0, 0, m_content.data());
}

void Label::Impl::Initialize(WINDOW *win) {
    
}


#pragma mark - Label functions

Label::Label(const std::string& content) :
View(static_cast<int>(content.length()), 1),
m_pimpl(new Impl(*this, content))
{ }

Label::~Label() { }

void Label::Update(const std::string &content) {
    m_pimpl->Update(content);
    
    //Update size
    SetWidth(static_cast<int>(content.length()));
}

void Label::Draw(WINDOW* win) const {
    m_pimpl->Draw(win);
}

void Label::Initialize(WINDOW* win) {
    m_pimpl->Initialize(win);
}
