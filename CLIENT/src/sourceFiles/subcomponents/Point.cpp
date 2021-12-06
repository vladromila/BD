#include "../../headers/subcomponents/Point.h"
#include "../../utils/GlobalVariables.h"
#include <bits/stdc++.h>

Point::Point()
{
}
Point::Point(int iX, int iY)
{
    x = iX;
    y = iY;
}

void Point::changeValues(int newX, int newY)
{
    x = newX;
    y = newY;
}

void Point::draw(Point origin, sf::RenderWindow &win)
{
    sf::CircleShape circle(POINT_CIRCLE_RADIUS);
    circle.setPosition(sf::Vector2f(origin.x + x - POINT_CIRCLE_RADIUS, origin.y + y - POINT_CIRCLE_RADIUS));
    circle.setFillColor(sf::Color(0, 0, 0));
    circle.setOutlineColor(sf::Color(255, 255, 255));
    circle.setOutlineThickness(1);

    win.draw(circle);
}

bool Point::isMouseOn(Point origin, Point mousePosition)
{
    sf::CircleShape circle(POINT_CIRCLE_RADIUS);
    circle.setPosition(sf::Vector2f(x - POINT_CIRCLE_RADIUS, y - POINT_CIRCLE_RADIUS));
    circle.setFillColor(sf::Color(0, 0, 0));
    circle.setOutlineColor(sf::Color(0, 0, 0));
    circle.setOutlineThickness(1);
    sf::FloatRect containingRect = circle.getGlobalBounds();
    if (containingRect.contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
        return true;
    return false;
}

void Point::rotatePoint(int ang)
{
    if (hasBeenRotated == false && hasBeenScaled == false)
        initialX = x, initialY = y;
    rotationAngle = ang;
    hasBeenRotated = true;
    float s = sin(ang * PI / 180.0);
    float c = cos(ang * PI / 180.0);
    Point fp;
    fp.x = (initialX * scale) * c - (initialY * scale) * s;
    fp.y = (initialX * scale) * s + (initialY * scale) * c;
    x = fp.x;
    y = fp.y;
}

void Point::scalePoint(float scaledAt)
{
    if (hasBeenRotated == false && hasBeenScaled == false)
        initialX = x, initialY = y;
    hasBeenScaled = true;
    scale = scaledAt;
    x = initialX * scale;
    y = initialY * scale;
    if (hasBeenRotated == true)
    {
        float s = sin(rotationAngle * PI / 180.0);
        float c = cos(rotationAngle * PI / 180.0);
        Point fp;
        fp.x = (x)*c - (y)*s;
        fp.y = (x)*s + (y)*c;
        x = fp.x;
        y = fp.y;
    }
}