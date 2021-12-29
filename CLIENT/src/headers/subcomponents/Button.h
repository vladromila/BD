#include <SFML/Graphics.hpp>
#include "../../sourceFiles/subcomponents/Rectangle.cpp"
class Button
{
    char btnText[25];
    Rectangle container;
    bool isHovered = false;
    // sf::Font font;
    int width;
    int height;
    int fontSize;
    sf::Color fill;
    sf::Color outline;
    sf::Color fillHover;
    sf::Color outlineHover;
    sf::Color fontColor;
    sf::Color fontColorHover;

public:
    Point topLeftCorner;
    Button();
    Button(Point topLeftCorner, int w, int h, int fontSize, const char btnText[]);
    Button(Point topLeftCorner, int w, int h, int fontSize, const char btnText[], sf::Color f, sf::Color o, sf::Color fh, sf::Color oh, sf::Color fontc, sf::Color fontch);
    void draw(sf::RenderWindow &win, sf::Font font);
    void drawCustom(sf::RenderWindow &win, sf::Font font);
    void onMouseMove(sf::Vector2f mousePos);
    bool onMousePress(sf::Vector2f mousePos);
};