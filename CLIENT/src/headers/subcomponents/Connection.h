#include <SFML/Graphics.hpp>
#include "../../sourceFiles/subcomponents/Point.cpp"
class Connection
{
public:
    Connection();
    int connectionInID = -1;
    int connectionOutID = -1;
    bool isDeleted = false;
    void draw(Point connectionIn, Point connectionOut, sf::RenderWindow &win);
};
