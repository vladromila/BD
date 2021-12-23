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
    bool isSecuredTextEntry=false;
    bool hasAddedIndicator=false;
    bool hasRemovedIndicator=true;
    sf::Font font;
    int width; 
    int height;
    int fontSize;

public:
    TextInput();
    TextInput(Point topLeftCorner,int w,int h,int fontSize,const char placeholder[],bool securedTextEntry);
    void onTextEntered(sf::Event e);
    void onMousePress(sf::Vector2f mousePos);
    void draw(sf::RenderWindow &win);
    void updateText(char t[]);
    char * getInputValue();
};