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

void Rectangle::draw(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win)
{
    sf::RectangleShape rectangle(sf::Vector2f(w, h));
    rectangle.setPosition(parentOrigin.x + topLeftCorner.x, parentOrigin.y + topLeftCorner.y);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color(255, 255, 255));
    rectangle.setOutlineThickness(3);
    rectangle.setScale(sf::Vector2f(scale, scale));
    rectangle.rotate(rotationAngle);
    win.draw(rectangle);
}