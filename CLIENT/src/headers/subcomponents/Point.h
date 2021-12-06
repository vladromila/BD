#include <SFML/Graphics.hpp>
#include "../../utils/GlobalVariables.h"
class Point
{
    int initialX, initialY;
    bool hasBeenRotated=false;
    bool hasBeenScaled=false;
    float scale=1;
    int rotationAngle=0;


public:
    int x, y;
    Point();
    Point(int initialX, int initialY);
    void rotatePoint(int ang);
    void scalePoint(float scaledAt);
    void changeValues(int newX, int newY);
    void draw(Point origin, sf::RenderWindow &win);
    bool isMouseOn(Point origin, Point mousePosition);
};