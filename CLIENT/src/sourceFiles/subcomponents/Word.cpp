#ifndef WORD_H
#define WORD_H

#include "../../headers/subcomponents/Word.h"

Word::Word()
{
}

Word::Word(Point topLeftCorner, int fontSize, const char btnText[])
{
    strcpy(this->btnText, btnText);
    Point containerOrigin(0, 0);
    this->topLeftCorner = topLeftCorner;
    font.loadFromFile("font.ttf");
    this->fontSize = fontSize;
}

void Word::draw(sf::RenderWindow &win)
{

    sf::Text btnTextComponent;
    btnTextComponent.setString(btnText);
    btnTextComponent.setFillColor(sf::Color::White);
    btnTextComponent.setCharacterSize(fontSize);
    btnTextComponent.setFont(font);

    sf::FloatRect textRect = btnTextComponent.getLocalBounds();
    btnTextComponent.setPosition(sf::Vector2f(topLeftCorner.x , topLeftCorner.y));
    btnTextComponent.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
    win.draw(btnTextComponent);
}

#endif