#ifndef BUTTON_H
#define BUTTON_H

#include "../../headers/subcomponents/Button.h"

Button::Button()
{
}

Button::Button(Point topLeftCorner, int w, int h, int fontSize, const char btnText[])
{
    width = w;
    height = h;
    strcpy(this->btnText, btnText);
    Point containerOrigin(0, 0);
    container = Rectangle(containerOrigin, width, height);
    this->topLeftCorner = topLeftCorner;
    font.loadFromFile("font.ttf");
    this->fontSize = fontSize;
}

void Button::onMouseMove(sf::Vector2f mousePos)
{
    if (container.isMouseOn(mousePos, topLeftCorner) == true)
        isHovered = true;
    else
        isHovered = false;
}

bool Button::onMousePress(sf::Vector2f mousePos)
{
    if (container.isMouseOn(mousePos, topLeftCorner) == true)
       return true;
    else
    return false;
}

void Button::draw(sf::RenderWindow &win)
{
    if (isHovered)
        container.drawAsSelected(topLeftCorner, 0, 1, win);
    else
        container.draw(topLeftCorner, 0, 1, win);

    sf::Text btnTextComponent;
    btnTextComponent.setString(btnText);
    btnTextComponent.setFillColor(sf::Color::White);
    btnTextComponent.setCharacterSize(fontSize);
    btnTextComponent.setFont(font);

    sf::FloatRect textRect = btnTextComponent.getLocalBounds();
    btnTextComponent.setPosition(sf::Vector2f(topLeftCorner.x + width / 2, topLeftCorner.y + height / 2 + (height - fontSize) * 0.25));
    btnTextComponent.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
    win.draw(btnTextComponent);
}

#endif