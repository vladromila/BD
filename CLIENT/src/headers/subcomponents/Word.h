#include <SFML/Graphics.hpp>
#include "../../sourceFiles/subcomponents/Rectangle.cpp"
class Word
{
    char btnText[25];
    bool isHovered = false;
    sf::Font font;
    int fontSize;

public:
    Point topLeftCorner;
    Word();
    Word(Point topLeftCorner,  int fontSize, const char btnText[]);
    void draw(sf::RenderWindow &win);
};