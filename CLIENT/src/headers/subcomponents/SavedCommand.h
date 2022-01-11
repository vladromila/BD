#include <SFML/Graphics.hpp>
#include "../../sourceFiles/subcomponents/Rectangle.cpp"

class SavedCommand
{
    Rectangle container;
    bool isHovered = false;
    bool isSelectable = false;
    // sf::Font font;
    int width;
    int height;
    int fontSize;
    sf::Color fill;
    sf::Color fillHover;
    sf::Color fontColor;
    sf::Color fontColorHover;

    sf::Text btnTextComponent;

public:
    Button deleteButton;
    std::string title;
    std::string id;
    Point topLeftCorner;
    SavedCommand();
    SavedCommand(std::string title, std::string id, int i);
    void draw(sf::RenderWindow &win, sf::Font font);
    void onMouseMove(sf::Vector2f mousePos);
    bool onMousePress(sf::Vector2f mousePos);
};