#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/Command.cpp"
#include "../../../sourceFiles/subcomponents/Slider.cpp"
#include "../../../sourceFiles/subcomponents/Connection.cpp"
#include "../../../sourceFiles/subcomponents/CommandModal.cpp"
#include "../../../sourceFiles/subcomponents/SaveAsModal.cpp"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
    Rectangle runResultContainer;
    int clientSocket;
    json userData;
    int actionsLength = -1;
    Action *actions;
    int commandsLength = -1;
    int commandId = -1;
    Command commands[50];
    int connectionsLength = -1;
    Connection connections[100];

    CommandModal commandModal;
    SaveAsModal saveAsModal;

    bool isFromInConnectionSelected = false;
    bool isFromOutConnectionSelected = false;

    int selectedInConnectionID = -1;
    int selectedOutConnectionID = -1;

    int defaultButtonsLength = 15;
    Button defaultButtons[16];
    Button quitButton;

    Slider rotationSlider;
    Slider scaleSlider;

    std::string selectedToAddCommand = "";

    int currentSelectedCommandIndex = -1;

    bool isMouseLongPressed = false;
    int xDiffOnLongPress = 0;
    int yDiffOnLongPress = 0;

    Point otherEnd;

    Button saveButton;
    Button saveAsButton;

    bool isCommandModalOpened = false;
    bool isSaveAsModalOpened = false;

    Point startPoint;
    Point endPoint;

    Button editComponent;
    Button deleteComponent;

    Button runCommand;
    Button runCommandLocally;

    Button closeRunResultScreen;
    Button openResultInBrowser;

    bool isRunnable = false;

    std::string toRunCommand;
    bool isRunResultScreenVisible = false;

    std::string toShowResult="";
    std::string commandForWebPreview="";
    bool hasPreparedOutput=false;

    sf::Text resultText;

public:
    std::string generalCommandName = "";
    std::string generalCommandId = "";
    CommandMaker();
    CommandMaker(int clientSocket, json userData);
    CommandMaker(int clientSocket, json userData, std::string data);
    void onMouseMove(sf::Vector2f mousePos);
    void onMouseRightPress(sf::Vector2f mousePos, sf::RenderWindow &win);
    std::string onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win);
    void onMouseRelease(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
    void draw(sf::RenderWindow &win, sf::Font font);
};