#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
#include "../../../sourceFiles/subcomponents/TextInput.cpp"
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/subcomponents/Word.cpp"
#include "../../../sourceFiles/subcomponents/SavedCommand.cpp"


using json = nlohmann::json;

class SavedCommands
{
    Word title;

    int clientSocket;
    json userData;
    SavedCommand commands[15];
    int commandsLength=0;

public:
    SavedCommands();
    SavedCommands(int clientSocket, json userData);
    void draw(sf::RenderWindow &win, sf::Font font);
    void onMouseMove(sf::Vector2f mousePos);
    std::string onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};