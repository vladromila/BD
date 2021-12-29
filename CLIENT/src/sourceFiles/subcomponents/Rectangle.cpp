#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "../../headers/subcomponents/Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Point origin, int width, int height)
{
    w = width;
    h = height;
    topLeftCorner.changeValues(origin.x, origin.y);
}

bool Rectangle::isMouseOn(sf::Vector2f mousePos, Point parentOrigin)
{
    sf::RectangleShape rectangle(sf::Vector2f(w, h));
    rectangle.setPosition(parentOrigin.x + topLeftCorner.x, parentOrigin.y + topLeftCorner.y);
    if (rectangle.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        return true;
    return false;
}

void Rectangle::draw(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win)
{
    sf::RectangleShape rectangle(sf::Vector2f(w, h));
    rectangle.setPosition(parentOrigin.x + topLeftCorner.x, parentOrigin.y + topLeftCorner.y);
    if (isTextInputContainer == true)
        rectangle.setFillColor(sf::Color::White);
    else
        rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color(255, 255, 255));
    rectangle.setOutlineThickness(3);
    rectangle.setScale(sf::Vector2f(scale, scale));
    rectangle.rotate(rotationAngle);
    win.draw(rectangle);
}

void Rectangle::drawAsSelected(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win)
{
    sf::RectangleShape rectangle(sf::Vector2f(w, h));
    rectangle.setPosition(parentOrigin.x + topLeftCorner.x, parentOrigin.y + topLeftCorner.y);
    if (isTextInputContainer == true)
        rectangle.setFillColor(sf::Color::White);
    else
        rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Yellow);
    rectangle.setOutlineThickness(3);
    rectangle.setScale(sf::Vector2f(scale, scale));
    rectangle.rotate(rotationAngle);
    win.draw(rectangle);
}

void Rectangle::drawCustom(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win, sf::Color fill, sf::Color outline)
{
    sf::RectangleShape rectangle(sf::Vector2f(w, h));
    rectangle.setPosition(parentOrigin.x + topLeftCorner.x, parentOrigin.y + topLeftCorner.y);
    rectangle.setFillColor(fill);
    rectangle.setOutlineColor(outline);
    rectangle.setOutlineThickness(3);
    rectangle.setScale(sf::Vector2f(scale, scale));
    rectangle.rotate(rotationAngle);
    win.draw(rectangle);
}
#endif