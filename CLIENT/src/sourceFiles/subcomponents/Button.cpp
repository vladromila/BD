#ifndef BUTTON_H
#define BUTTON_H

#include "../../headers/subcomponents/Button.h"
#include <nlohmann/json.hpp>

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
    this->fontSize = fontSize;
}

Button::Button(Point topLeftCorner, int w, int h, int fontSize, const char btnText[], sf::Color f, sf::Color o, sf::Color fh, sf::Color oh, sf::Color fontc, sf::Color fontch)
{
    fontColor = fontc;
    fontColorHover = fontch;
    fill = f;
    outline = o;
    fillHover = fh;
    outlineHover = oh;
    width = w;
    height = h;
    strcpy(this->btnText, btnText);
    Point containerOrigin(0, 0);
    container = Rectangle(containerOrigin, width, height);
    this->topLeftCorner = topLeftCorner;
    this->fontSize = fontSize;
}

Button::Button(Point topLeftCorner, int w, int h, int fontSize, const char btnText[], sf::Color f, sf::Color o, sf::Color fh, sf::Color oh, sf::Color fontc, sf::Color fontch, sf::Color sf, sf::Color sff, bool selectable)
{
    isSelectable = selectable;
    selectedColor = sf;
    fontSelectedColo = sff;
    fontColor = fontc;
    fontColorHover = fontch;
    fill = f;
    outline = o;
    fillHover = fh;
    outlineHover = oh;
    width = w;
    height = h;
    strcpy(this->btnText, btnText);
    Point containerOrigin(0, 0);
    container = Rectangle(containerOrigin, width, height);
    this->topLeftCorner = topLeftCorner;
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

void Button::draw(sf::RenderWindow &win, sf::Font font)
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
    btnTextComponent.setPosition(sf::Vector2f(topLeftCorner.x + width / 2, topLeftCorner.y + (height - fontSize) / 1.75));
    btnTextComponent.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top);
    win.draw(btnTextComponent);
}

void Button::drawCustom(sf::RenderWindow &win, sf::Font font)
{
    if (isSelected)
        container.drawCustom(topLeftCorner, 0, 1, win, selectedColor, selectedColor);
    else if (isHovered)
        container.drawCustom(topLeftCorner, 0, 1, win, fillHover, outlineHover);
    else
        container.drawCustom(topLeftCorner, 0, 1, win, fill, outline);

    sf::Text btnTextComponent;
    btnTextComponent.setString(btnText);
    if (isSelected)
        btnTextComponent.setFillColor(fontSelectedColo);
    else if (isHovered)
        btnTextComponent.setFillColor(fontColorHover);
    else
        btnTextComponent.setFillColor(fontColor);
    btnTextComponent.setCharacterSize(fontSize);
    btnTextComponent.setFont(font);

    sf::FloatRect textRect = btnTextComponent.getLocalBounds();
    btnTextComponent.setPosition(sf::Vector2f(topLeftCorner.x + width / 2, topLeftCorner.y + (height - fontSize) / 1.75));
    btnTextComponent.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top);
    win.draw(btnTextComponent);
}

#endif