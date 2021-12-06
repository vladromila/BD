#include "../../sourceFiles/subcomponents/Point.cpp"
class Rectangle
{
public:
    Point topLeftCorner;
    int w, h;
    Rectangle();
    Rectangle(Point origin, int width, int height);
    void draw(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win);
};