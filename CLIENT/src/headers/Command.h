#include <SFML/Graphics.hpp>
#include "../sourceFiles/subcomponents/Rectangle.cpp"
class Command
{
    Point topLeftCorner;
    Point connectionIn;
    Point connectionOut;
    char commandName[20];
    float scale=1;
    int rotationAngle=0;
    Rectangle container;
    sf::Font font;

public:
    Command(const char *commandName,Point origin);
    void rotate(int rot);
    void draw(sf::RenderWindow &win);
};