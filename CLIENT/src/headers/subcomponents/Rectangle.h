
#include "../../sourceFiles/subcomponents/Point.cpp"
class Rectangle
{
public:
    Point topLeftCorner;
    int w, h;
    bool isTextInputContainer = false;
    Rectangle();
    Rectangle(Point origin, int width, int height);
    bool isMouseOn(sf::Vector2f mousePos, Point parentOrigin);
    void draw(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win);
    void drawAsSelected(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win);
    void drawCustom(Point parentOrigin, int rotationAngle, float scale, sf::RenderWindow &win,sf::Color fill,sf::Color border);
};
