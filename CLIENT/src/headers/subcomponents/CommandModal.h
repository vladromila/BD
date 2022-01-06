#include "../../sourceFiles/subcomponents/TextInput.cpp"
#include "../../sourceFiles/subcomponents/Button.cpp"
#include "../../sourceFiles/subcomponents/Word.cpp"

class CommandModal
{
    std::string parametersString;
    Button closeButton;
    Button deleteButton;
    Button saveButton;
    Rectangle container;
    sf::Text title;
    sf::RectangleShape mainContainer;

public:
    TextInput parameters;
    CommandModal();
    void onMouseMove(sf::Vector2f mousePos);
    std::string onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
    void draw(sf::RenderWindow &win, sf::Font font);
};