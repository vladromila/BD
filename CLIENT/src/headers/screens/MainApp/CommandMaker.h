#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/Command.cpp"

using json = nlohmann::json;

class CommandMaker
{
    Rectangle container;
    int clientSocket;
    json userData;
    Command c1;
    Command c2;

public:
    CommandMaker();
    CommandMaker(int clientSocket, json userData);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win);
    void onTextEntered(sf::Event e);
    void draw(sf::RenderWindow &win, sf::Font font);
};