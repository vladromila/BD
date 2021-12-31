#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/Command.cpp"
#include "../../../sourceFiles/subcomponents/Slider.cpp"

using json = nlohmann::json;

struct Action
{
    std::string type;
    Point previousComponentTopLeftCorner;
    float previousScaledAt;
    int previousRotatedAt;

    Point usedComponentNewTopLeftCorner;
    float scaledAt = 1;
    int rotatedAt = 0;
    int oldComponentId = -1;
    int oldPointIndex = -1;
    int pointIndex = -1;
    int connectionId = -1;
    int componentId = -1;
};

class CommandMaker
{
    Rectangle container;
    int clientSocket;
    json userData;
    int actionsLength = -1;
    Action *actions;
    int commandsLength = -1;
    Command commands[50];
    int defaultButtonsLength = 9;
    Button defaultButtons[10];

    Slider rotationSlider;
    Slider scaleSlider;

    std::string selectedToAddCommand = "";

    int currentSelectedCommandIndex=-1;

    bool isMouseLongPressed=false;
    int xDiffOnLongPress=0;
    int yDiffOnLongPress=0;

public:
    CommandMaker();
    CommandMaker(int clientSocket, json userData);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos);
    void onMouseRelease(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
    void draw(sf::RenderWindow &win, sf::Font font);
};