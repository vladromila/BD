#include <SFML/Graphics.hpp>
#include "../../sourceFiles/subcomponents/Rectangle.cpp"
#include "../../utils/GlobalVariables.h"
class TextInput
{
    char input[100];
    char placeholder[50];
    Rectangle container;
    Point topLeftCorner;
    bool isSelected = false;
    sf::Font font;

public:
    TextInput();
    TextInput(Point topLeftCorner,const char placeholder[]);
    void onTextEntered(sf::Event e);
    void onClick(sf::Vector2f mousePos);
    void draw(sf::RenderWindow &win);
    void updateText(char t[]);
};