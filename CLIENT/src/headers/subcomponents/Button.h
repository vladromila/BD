#include <SFML/Graphics.hpp>
#include "../../sourceFiles/subcomponents/Rectangle.cpp"
class Button
{
    char btnText[25];
    Rectangle container;
    bool isHovered = false;
    sf::Font font;
    int width;
    int height;
    int fontSize;

public:
    Point topLeftCorner;
    Button();
    Button(Point topLeftCorner, int w, int h, int fontSize, const char btnText[]);
    void draw(sf::RenderWindow &win);
    void onMouseMove(sf::Vector2f mousePos);
    bool onMousePress(sf::Vector2f mousePos);
};