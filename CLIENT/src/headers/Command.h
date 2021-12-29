#include <SFML/Graphics.hpp>
#include "../sourceFiles/subcomponents/Rectangle.cpp"

class Command
{
    Point topLeftCorner;
    Point connectionIn;
    Point connectionOut;
    std::string commandName;
    float scale = 1;
    int rotationAngle = 0;
    Rectangle container;

public:
    Command();
    Command(std::string commandName, Point origin);
    void rotate(int rot);
    void draw(sf::RenderWindow &win, sf::Font font);
};