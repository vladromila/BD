#include <SFML/Graphics.hpp>
#include "../sourceFiles/subcomponents/Rectangle.cpp"

class Command
{
    std::string commandName;
    bool hasSetOrigin=false;
    Rectangle container;
    Rectangle selectedContainer;
    sf::Text letterComponent;

public:
    Point connectionIn;
    Point connectionOut;
    Point cip;
    Point cop;
    int id;
    Point topLeftCorner;
    bool isSelected = false;
    float scale = 1;
    int rotationAngle = 0;
int initialLetterX;
    Command();
    Command(std::string commandName, Point origin,int id);
    void rotateAt(int rot);
    void scaleAt(float scale);
    bool onMousePress(sf::Vector2f mousePos);
    void draw(sf::RenderWindow &win, sf::Font font);
};