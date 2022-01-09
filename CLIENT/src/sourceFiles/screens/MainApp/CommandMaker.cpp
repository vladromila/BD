#include "../../../headers/screens/MainApp/CommandMaker.h"

std::wstring to_wide(const std::string &multi)
{
    std::wstring wide;
    wchar_t w;
    mbstate_t mb{};
    size_t n = 0, len = multi.length() + 1;
    while (auto res = mbrtowc(&w, multi.c_str() + n, len - n, &mb))
    {
        if (res == size_t(-1) || res == size_t(-2))
            throw "invalid encoding";

        n += res;
        wide += w;
    }
    return wide;
}

CommandMaker::CommandMaker()
{
}

CommandMaker::CommandMaker(int clientSocket, json userData) : container(Point(sf::VideoMode::getDesktopMode().width * 0.1 + 9, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.93),
                                                              runResultContainer(Point(0, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.93),
                                                              rotationSlider(sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().width * 0.05 - 250, sf::VideoMode::getDesktopMode().height - 30, 0),
                                                              scaleSlider(sf::VideoMode::getDesktopMode().width - 50, sf::VideoMode::getDesktopMode().height - sf::VideoMode::getDesktopMode().height * 0.05 - 160, 1)
{
    rotationSlider.create(0, 360);
    scaleSlider.create(3, 8);

    saveButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.1 + 9, 3), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.07 - 9, sf::VideoMode::getDesktopMode().height * 0.045, "Save", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    saveAsButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.20 + 18, 3), sf::VideoMode::getDesktopMode().width * 0.14, sf::VideoMode::getDesktopMode().height * 0.07 - 9, sf::VideoMode::getDesktopMode().height * 0.045, "Save As", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    quitButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.975 - 9, sf::VideoMode::getDesktopMode().height * 0.95 - 6), sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.031, "X");

    endPoint = Point(sf::VideoMode().getDesktopMode().width - 41, sf::VideoMode().getDesktopMode().height * 0.55);

    commands[++commandsLength] = Command("", Point(sf::VideoMode().getDesktopMode().width * 0.1, sf::VideoMode().getDesktopMode().height * 0.45), ++commandId);
    commands[++commandsLength] = Command("", Point(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height * 0.45), ++commandId);
    commands[0].isStartCommand = true;
    commands[1].isEndCommand = true;
    defaultButtons[0] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "custom", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[1] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.12 + 9), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[2] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.17 + 18), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ls", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[3] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.22 + 27), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cat", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[4] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.27 + 36), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cp", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[5] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.32 + 45), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "mv", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[6] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.37 + 54), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "mkdir", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[7] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.42 + 63), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "pwd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[8] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.47 + 72), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "rm", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[9] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.52 + 81), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "touch", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[10] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.57 + 90), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "locate", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[11] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.62 + 99), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "find", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[12] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.67 + 108), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "grep", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[13] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.72 + 117), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ps", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[14] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.77 + 126), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "kill", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    this->clientSocket = clientSocket;
    this->userData = userData;

    runCommand = Button(Point(sf::VideoMode().getDesktopMode().width * 0.92, sf::VideoMode().getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.08, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.025, "Run", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    runCommandLocally = Button(Point(sf::VideoMode().getDesktopMode().width * 0.8 - 9, sf::VideoMode().getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.12, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.025, "Run locally", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    deleteComponent = Button(Point(sf::VideoMode().getDesktopMode().width * 0.1 + 9, sf::VideoMode::getDesktopMode().height * 0.95 - 9), sf::VideoMode::getDesktopMode().width * 0.065, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "Delete", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White);
    editComponent = Button(Point(sf::VideoMode().getDesktopMode().width * 0.16 + 27, sf::VideoMode::getDesktopMode().height * 0.95 - 9), sf::VideoMode::getDesktopMode().width * 0.065, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "Edit", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White);
}

CommandMaker::CommandMaker(int clientSocket, json userData, std::string data) : container(Point(sf::VideoMode::getDesktopMode().width * 0.1 + 9, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.93),
                                                                                runResultContainer(Point(0, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.93),
                                                                                rotationSlider(sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().width * 0.05 - 250, sf::VideoMode::getDesktopMode().height - 30, 0),
                                                                                scaleSlider(sf::VideoMode::getDesktopMode().width - 50, sf::VideoMode::getDesktopMode().height - sf::VideoMode::getDesktopMode().height * 0.05 - 160, 1)
{
    rotationSlider.create(0, 360);
    scaleSlider.create(3, 8);

    saveButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.1 + 9, 3), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.07 - 9, sf::VideoMode::getDesktopMode().height * 0.045, "Save", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    saveAsButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.20 + 18, 3), sf::VideoMode::getDesktopMode().width * 0.14, sf::VideoMode::getDesktopMode().height * 0.07 - 9, sf::VideoMode::getDesktopMode().height * 0.045, "Save As", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    quitButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.975 - 9, sf::VideoMode::getDesktopMode().height * 0.95 - 6), sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.031, "X");

    endPoint = Point(sf::VideoMode().getDesktopMode().width - 41, sf::VideoMode().getDesktopMode().height * 0.55);

    runCommand = Button(Point(sf::VideoMode().getDesktopMode().width * 0.92, sf::VideoMode().getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.08, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.025, "Run", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    runCommandLocally = Button(Point(sf::VideoMode().getDesktopMode().width * 0.8 - 9, sf::VideoMode().getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.12, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.025, "Run locally", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    commands[++commandsLength] = Command("", Point(sf::VideoMode().getDesktopMode().width * 0.1, sf::VideoMode().getDesktopMode().height * 0.45), ++commandId);
    commands[++commandsLength] = Command("", Point(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height * 0.45), ++commandId);
    commands[0].isStartCommand = true;
    commands[1].isEndCommand = true;
    defaultButtons[0] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "custom", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[1] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.12 + 9), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[2] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.17 + 18), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ls", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[3] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.22 + 27), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cat", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[4] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.27 + 36), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cp", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[5] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.32 + 45), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "mv", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[6] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.37 + 54), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "mkdir", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[7] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.42 + 63), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "pwd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[8] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.47 + 72), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "rm", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[9] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.52 + 81), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "touch", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[10] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.57 + 90), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "locate", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[11] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.62 + 99), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "find", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[12] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.67 + 108), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "grep", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[13] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.72 + 117), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ps", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[14] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.77 + 126), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "kill", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    this->clientSocket = clientSocket;
    this->userData = userData;

    deleteComponent = Button(Point(sf::VideoMode().getDesktopMode().width * 0.1 + 9, sf::VideoMode::getDesktopMode().height * 0.95 - 9), sf::VideoMode::getDesktopMode().width * 0.065, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "Delete", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White);
    editComponent = Button(Point(sf::VideoMode().getDesktopMode().width * 0.16 + 27, sf::VideoMode::getDesktopMode().height * 0.95 - 9), sf::VideoMode::getDesktopMode().width * 0.065, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "Edit", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White);

    json dt = json::parse(data);
    commandId = dt["biggestID"];

    for (const auto &item : dt["commands"].items())
    {
        commands[++commandsLength] = Command(item.value()["commandName"], Point(item.value()["x"], item.value()["y"]), item.value()["id"]);
        commands[commandsLength].parameters = item.value()["parameters"];
        commands[commandsLength].requiresAndOp = item.value()["requiresAndOp"];
    }

    for (const auto &item : dt["connections"].items())
    {
        connections[++connectionsLength].connectionInID = item.value()["connectionInID"];
        connections[connectionsLength].connectionOutID = item.value()["connectionOutID"];
    }
}

void CommandMaker::onMouseMove(sf::Vector2f mousePos)
{
    if (isCommandModalOpened)
    {

        commandModal.onMouseMove(mousePos);
    }
    else if (isSaveAsModalOpened)
    {
        saveAsModal.onMouseMove(mousePos);
    }
    else
    {

        if (rotationSlider.isActivated == true)
            if (currentSelectedCommandIndex != -1)
                commands[currentSelectedCommandIndex].rotateAt(rotationSlider.getSliderValue());
        if (scaleSlider.isActivated == true)
            if (currentSelectedCommandIndex != -1)
                commands[currentSelectedCommandIndex].scaleAt(scaleSlider.getSliderValue() / 4.0f);
        if (isMouseLongPressed == true && currentSelectedCommandIndex != -1 && rotationSlider.isActivated == false && scaleSlider.isActivated == false)
        {
            commands[currentSelectedCommandIndex].topLeftCorner.x = mousePos.x - xDiffOnLongPress;
            commands[currentSelectedCommandIndex].topLeftCorner.y = mousePos.y - yDiffOnLongPress;
        }
        for (int i = 0; i < defaultButtonsLength; i++)
            defaultButtons[i].onMouseMove(mousePos);
        editComponent.onMouseMove(mousePos);
        deleteComponent.onMouseMove(mousePos);
        quitButton.onMouseMove(mousePos);
        if (isRunnable)
        {
            runCommandLocally.onMouseMove(mousePos);
            runCommand.onMouseMove(mousePos);
        }
        if (isFromInConnectionSelected || isFromOutConnectionSelected)
        {
            otherEnd.x = mousePos.x;
            otherEnd.y = mousePos.y;
        }

        saveButton.onMouseMove(mousePos);
        saveAsButton.onMouseMove(mousePos);
    }
}

void CommandMaker::onTextEntered(sf::Event e)
{
    if (isCommandModalOpened)
        commandModal.onTextEntered(e);
    if (isSaveAsModalOpened)
        saveAsModal.onTextEntered(e), saveAsModal.generalCommandName.resetError();
}

void CommandMaker::onMouseRightPress(sf::Vector2f mousePos, sf::RenderWindow &win)
{
    if (isCommandModalOpened == false)
    {
        commandModal.onMouseMove(sf::Vector2f(0, 0));
        bool isACommandSelected = false;
        int commandSelectedIndex = -1;

        for (int i = 0; i <= commandsLength; i++)
            if (commands[i].onMousePress(mousePos))
                isACommandSelected = true, commandSelectedIndex = i;
        if (isACommandSelected == true)
        {
            if (commandSelectedIndex != currentSelectedCommandIndex)
            {
                for (int i = 0; i <= commandsLength; i++)
                    commands[i].isSelected = false;
            }
            isCommandModalOpened = true;
            currentSelectedCommandIndex = commandSelectedIndex;
            commands[commandSelectedIndex].isSelected = true;
            strcpy(commandModal.parameters.input, commands[currentSelectedCommandIndex].parameters.c_str());
            commandModal.requiredAndOp.isSelected = commands[currentSelectedCommandIndex].requiresAndOp;
        }
    }
}

void CommandMaker::onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win)
{
    if (runCommand.onMousePress(mousePos) || runCommandLocally.onMousePress(mousePos))
    {
        json reqJson;
        reqJson["reqType"] = "runCommand";
        reqJson["toRunCommand"] = toRunCommand;
        time_t _tm = time(NULL);
        struct tm *curtime = localtime(&_tm);
        std::string dateString = std::string(asctime(curtime));

        dateString.pop_back();
        dateString.erase(remove_if(dateString.begin(), dateString.end(), isspace), dateString.end());

        reqJson["execDate"] = dateString;
        reqJson["email"] = userData["email"];

        std::string req = std::to_string(reqJson.dump().length() + 1);
        req += '~';
        req += reqJson.dump();
        send(clientSocket, req.c_str(), req.length() + 1, 0);
        char nr[10];
        char buffer[100000];
        recv(clientSocket, buffer, 1, 0);
        while (buffer[0] != '~')
        {
            buffer[1] = '\0';
            strcat(nr, buffer);
            bzero(buffer, sizeof(buffer));
            recv(clientSocket, buffer, 1, 0);
        }
        bzero(buffer, sizeof(buffer));

        // printf("%s\n", nr);

        int bufSize = atoi(nr);
        bzero(nr, sizeof(nr));

        recv(clientSocket, buffer, bufSize + 1, 0);
        json res = json::parse(buffer);
        printf("%s\n", res.dump().c_str());
        isRunResultScreenVisible = true;
        toShowResult = res["response"];
        printf("%s", toShowResult.c_str());
    }
    else if (isCommandModalOpened)
    {
        std::string res = commandModal.onMousePress(mousePos);
        json resJson = json::parse(res);
        if (resJson["close"] == true)
            isCommandModalOpened = false;
        else if (resJson["delete"] == true)
        {
            int id = commands[currentSelectedCommandIndex].id;
            commands[currentSelectedCommandIndex].isDeleted = true;
            for (int i = 0; i <= connectionsLength; i++)
                if (connections[i].connectionInID == id || connections[i].connectionOutID == id)
                    connections[i].isDeleted = true;
            isCommandModalOpened = false;
        }
        else if (resJson["save"] == true)
        {
            commands[currentSelectedCommandIndex].requiresAndOp = commandModal.requiredAndOp.isSelected;
            commands[currentSelectedCommandIndex].parameters = std::string(commandModal.parameters.input);
            isCommandModalOpened = false;
        }
    }
    else if (isSaveAsModalOpened)
    {
        saveAsModal.generalCommandName.resetError();
        std::string res = saveAsModal.onMousePress(mousePos);
        json resJson = json::parse(res);
        if (resJson["isCanceled"] == true)
            isSaveAsModalOpened = false;
        else if (resJson["isSaved"] == true)
        {
            json req;
            req["reqType"] = "saveNewCommand";
            req["email"] = userData["email"];
            req["commandName"] = std::string(saveAsModal.generalCommandName.getInputValue());

            json data;
            auto comp = json::array();
            for (int i = 2; i <= commandsLength; i++)
            {
                if (commands[i].isDeleted == false)
                {
                    json comm;
                    comm["scale"] = commands[i].scale;
                    comm["rotationAngle"] = commands[i].rotationAngle;
                    comm["commandName"] = commands[i].commandName;
                    comm["parameters"] = commands[i].parameters;
                    comm["x"] = commands[i].topLeftCorner.x;
                    comm["y"] = commands[i].topLeftCorner.y;
                    comm["id"] = commands[i].id;

                    comp.push_back(comm);
                }
            }
            data["commands"] = comp;
            auto conn = json::array();
            for (int i = 0; i <= connectionsLength; i++)
            {
                if (connections[i].isDeleted == false)
                {
                    json con;
                    con["connectionInID"] = connections[i].connectionInID;
                    con["connectionOutID"] = connections[i].connectionOutID;

                    conn.push_back(con);
                }
            }
            data["connections"] = conn;
            data["biggestID"] = commandId;

            req["commandData"] = data.dump();

            std::string reqString = std::to_string(req.dump().length() + 1);
            reqString += '~';
            reqString += req.dump();

            send(clientSocket, reqString.c_str(), reqString.length() + 1, 0);

            char res[1024];
            recv(clientSocket, res, 1024, 0);
            json resJson = json::parse(res);
            if (resJson["success"] == false)
            {
                saveAsModal.generalCommandName.changeError(resJson["saveError"]);
            }
            else
            {
                printf("%s\n", resJson.dump().c_str());
                generalCommandId = resJson["commandId"];
                generalCommandName = std::string(saveAsModal.generalCommandName.getInputValue());
                isSaveAsModalOpened = false;
            }
            // isSaveAsModalOpened = false;
        }
    }
    else if (saveButton.onMousePress(mousePos) || saveAsButton.onMousePress(mousePos))
    {
        if (saveAsButton.onMousePress(mousePos))
            isSaveAsModalOpened = true;
        if (saveButton.onMousePress(mousePos))
        {
            if (generalCommandId == "")
                isSaveAsModalOpened = true;
            else
            {
                json req;
                req["reqType"] = "saveCommand";
                req["commandId"] = generalCommandId;

                json data;
                auto comp = json::array();
                for (int i = 2; i <= commandsLength; i++)
                {
                    if (commands[i].isDeleted == false)
                    {
                        json comm;
                        comm["scale"] = commands[i].scale;
                        comm["rotationAngle"] = commands[i].rotationAngle;
                        comm["commandName"] = commands[i].commandName;
                        comm["parameters"] = commands[i].parameters;
                        comm["x"] = commands[i].topLeftCorner.x;
                        comm["y"] = commands[i].topLeftCorner.y;
                        comm["id"] = commands[i].id;

                        comp.push_back(comm);
                    }
                }
                data["commands"] = comp;
                auto conn = json::array();
                for (int i = 0; i <= connectionsLength; i++)
                {
                    if (connections[i].isDeleted == false)
                    {
                        json con;
                        con["connectionInID"] = connections[i].connectionInID;
                        con["connectionOutID"] = connections[i].connectionOutID;

                        conn.push_back(con);
                    }
                }
                data["connections"] = conn;
                data["biggestID"] = commandId;

                req["commandData"] = data.dump();

                std::string reqString = std::to_string(req.dump().length() + 1);
                reqString += '~';
                reqString += req.dump();

                send(clientSocket, reqString.c_str(), reqString.length() + 1, 0);

                char res[1024];
                recv(clientSocket, res, 1024, 0);
                json resJson = json::parse(res);
                if (resJson["success"] == false)
                {
                }
                else
                {
                }
            }
        }
    }
    else
    {
        isMouseLongPressed = true;

        bool isACommandSelected = false;
        int commandSelectedIndex = -1;
        bool isOnRotationSlider = rotationSlider.isMouseOn(mousePos);
        bool isOnScaleSlider = scaleSlider.isMouseOn(mousePos);

        bool moveOn = true;
        if (currentSelectedCommandIndex != -1)
            if (editComponent.onMousePress(mousePos) == true)
            {
                isCommandModalOpened = true;
                strcpy(commandModal.parameters.input, commands[currentSelectedCommandIndex].parameters.c_str());
                commandModal.requiredAndOp.isSelected = commands[currentSelectedCommandIndex].requiresAndOp;
                moveOn = false;
            }
            else if (deleteComponent.onMousePress(mousePos) == true)
            {
                int id = commands[currentSelectedCommandIndex].id;
                commands[currentSelectedCommandIndex].isDeleted = true;
                for (int i = 0; i <= connectionsLength; i++)
                    if (connections[i].connectionInID == id || connections[i].connectionOutID == id)
                        connections[i].isDeleted = true;
                moveOn = false;
            }
        if (quitButton.onMousePress(mousePos))
        {
            moveOn = false;
            send(clientSocket, "5~exit", 6, 0);
            close(clientSocket);
            win.close();
        }
        if (moveOn)
        {
            for (int i = 0; i <= commandsLength; i++)
                if (commands[i].onMousePress(mousePos) && commands[i].isDeleted == false)
                    isACommandSelected = true, commandSelectedIndex = i;
            for (int i = 0; i <= commandsLength; i++)
            {
                if (commands[i].connectionIn.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
                {
                    bool isAlreadyConnected = false;
                    for (int j = 0; j <= connectionsLength; j++)
                        if (connections[j].isDeleted == false && connections[j].connectionInID == commands[i].id)
                        {
                            isFromOutConnectionSelected = true;
                            selectedOutConnectionID = connections[j].connectionOutID;
                            connections[j].isDeleted = true;
                            isAlreadyConnected = true;
                        }
                    if (isAlreadyConnected == false)
                    {
                        isFromInConnectionSelected = true;
                        selectedInConnectionID = commands[i].id;
                    }
                }
                if (isFromInConnectionSelected == true)
                {
                    isFromOutConnectionSelected = false;
                    selectedOutConnectionID = -1;
                }
                else if (isFromOutConnectionSelected == false)
                {
                    if (commands[i].connectionOut.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
                    {
                        bool isAlreadyConnected = false;
                        for (int j = 0; j <= connectionsLength; j++)
                            if (connections[j].isDeleted == false && connections[j].connectionOutID == commands[i].id)
                            {
                                isFromInConnectionSelected = true;
                                selectedInConnectionID = connections[j].connectionInID;
                                connections[j].isDeleted = true;
                                isAlreadyConnected = true;
                            }
                        if (isAlreadyConnected == false)
                        {
                            isFromOutConnectionSelected = true;
                            selectedOutConnectionID = commands[i].id;
                        }
                    }
                }
            }
            if (isFromOutConnectionSelected || isFromInConnectionSelected)
            {
                for (int i = 0; i <= commandsLength; i++)
                    commands[i].isSelected = false;
                currentSelectedCommandIndex = -1;
                otherEnd.x = mousePos.x;
                otherEnd.y = mousePos.y;
            }
            else if (selectedToAddCommand != "")
            {
                if (isACommandSelected == false)
                {
                    if (mousePos.x > sf::VideoMode::getDesktopMode().width * 0.1 + 100 && mousePos.y > sf::VideoMode::getDesktopMode().height * 0.1 + 20 && isOnScaleSlider == false && isOnRotationSlider == false)
                    {
                        if (currentSelectedCommandIndex != -1)
                        {
                            commands[currentSelectedCommandIndex].isSelected = false;
                            currentSelectedCommandIndex = -1;
                        }
                        commandsLength++;
                        currentSelectedCommandIndex = commandsLength;
                        commands[commandsLength] = Command(selectedToAddCommand, Point(mousePos.x, mousePos.y), ++commandId);
                        commands[commandsLength].isSelected = true;
                        xDiffOnLongPress = 0;
                        yDiffOnLongPress = 0;
                    }
                    else if (currentSelectedCommandIndex != -1)
                    {
                        if (isOnRotationSlider == false && isOnScaleSlider == false)
                        {
                            commands[currentSelectedCommandIndex].isSelected = false;
                            currentSelectedCommandIndex = -1;
                        }
                    }
                }
                else
                {
                    if (currentSelectedCommandIndex != commandSelectedIndex)
                    {
                        commands[currentSelectedCommandIndex].isSelected = false;
                        commands[commandSelectedIndex].isSelected = true;
                        currentSelectedCommandIndex = commandSelectedIndex;
                    }

                    yDiffOnLongPress = mousePos.y - commands[commandSelectedIndex].topLeftCorner.y;
                    xDiffOnLongPress = mousePos.x - commands[commandSelectedIndex].topLeftCorner.x;
                }
            }
            else if (isACommandSelected == true && commandSelectedIndex > 1)
            {
                if (commandSelectedIndex != currentSelectedCommandIndex)
                    commands[currentSelectedCommandIndex].isSelected = false, currentSelectedCommandIndex = commandSelectedIndex;
                commands[commandSelectedIndex].isSelected = true;
                yDiffOnLongPress = mousePos.y - commands[commandSelectedIndex].topLeftCorner.y;
                xDiffOnLongPress = mousePos.x - commands[commandSelectedIndex].topLeftCorner.x;
            }
            else
            {
                if (currentSelectedCommandIndex != -1)
                    if (isOnScaleSlider == true || isOnRotationSlider == true)
                    {
                        if (isOnRotationSlider)
                            commands[currentSelectedCommandIndex].rotateAt(rotationSlider.getSliderValue());
                        if (isOnScaleSlider)
                            commands[currentSelectedCommandIndex].scaleAt(scaleSlider.getSliderValue() / 4.0f);
                    }
                    else
                        commands[currentSelectedCommandIndex].isSelected = false, currentSelectedCommandIndex = -1;
            }
            if (isACommandSelected == false)
                for (int i = 0; i < defaultButtonsLength; i++)
                    if (defaultButtons[i].onMousePress(mousePos))
                        if (defaultButtons[i].isSelected == false)
                        {
                            for (int j = 0; j < defaultButtonsLength; j++)
                                defaultButtons[j].isSelected = false;
                            defaultButtons[i].isSelected = true;
                            selectedToAddCommand = std::string(defaultButtons[i].btnText);
                        }
                        else
                            defaultButtons[i].isSelected = false, selectedToAddCommand = "";
            if (quitButton.onMousePress(mousePos))
            {
                send(clientSocket, "5~exit", 6, 0);
                close(clientSocket);
                win.close();
            }
        }
    }
}

void CommandMaker::onMouseRelease(sf::Vector2f mousePos)
{
    isMouseLongPressed = false;
    if (rotationSlider.isActivated == true)
        rotationSlider.isActivated = false;
    if (scaleSlider.isActivated == true)
        scaleSlider.isActivated = false;

    for (int i = 0; i <= commandsLength; i++)
    {
        if (isFromInConnectionSelected)
        {
            if (commands[i].connectionOut.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
            {
                if (selectedInConnectionID != commands[i].id)
                {
                    bool isAlreadyConnected = false;
                    for (int j = 0; j <= connectionsLength; j++)
                        if (connections[j].isDeleted == true && connections[j].connectionInID == selectedInConnectionID && connections[j].connectionOutID == commands[i].id)
                        {
                            isAlreadyConnected = true;
                            connections[j].isDeleted = false;
                        }
                    if (isAlreadyConnected == false)
                    {
                        connections[++connectionsLength].connectionInID = selectedInConnectionID;
                        connections[connectionsLength].connectionOutID = commands[i].id;
                    }
                }
            }
        }
        if (isFromOutConnectionSelected)
        {
            if (commands[i].connectionIn.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
            {
                if (selectedOutConnectionID != commands[i].id)
                {
                    bool isAlreadyConnected = false;
                    for (int j = 0; j <= connectionsLength; j++)
                        if (connections[j].isDeleted == true && connections[j].connectionInID == commands[i].id && connections[j].connectionOutID == selectedOutConnectionID)
                        {
                            isAlreadyConnected = true;
                            connections[j].isDeleted = false;
                        }
                    if (isAlreadyConnected == false)
                    {
                        connections[++connectionsLength].connectionInID = commands[i].id;
                        connections[connectionsLength].connectionOutID = selectedOutConnectionID;
                    }
                }
            }
        }
    }

    selectedOutConnectionID = -1;
    selectedInConnectionID = -1;
    isFromOutConnectionSelected = false;
    isFromInConnectionSelected = false;

    int currentId = 0;
    toRunCommand = "";
    int j = 0;
    while (currentId != 1)
    {
        bool hasAOutConnection = false;
        for (int i = 0; i <= connectionsLength; i++)
            if (connections[i].connectionOutID == currentId && connections[i].isDeleted == false)
            {
                j++;
                hasAOutConnection = true;
                currentId = connections[i].connectionInID;
                for (int k = 0; k <= commandsLength; k++)
                {
                    if (commands[k].id == currentId && currentId != 0 && currentId != 1)
                    {
                        if (j > 1)
                        {
                            if (commands[k].requiresAndOp)
                            {
                                toRunCommand += " && ";
                            }
                            else
                                toRunCommand += " | ";
                        }
                        toRunCommand += commands[k].commandName;
                        toRunCommand += " ";
                        toRunCommand += commands[k].parameters;
                    }
                }
                if (currentId == 1)
                    isRunnable = true;
            }
        if (hasAOutConnection == false)
        {
            currentId = 1;
            isRunnable = false;
        }
    }
    if (isRunnable == true)
    {
        // printf("%s\n", toRunCommand.c_str());
        json data;
        auto comp = json::array();
        for (int i = 2; i <= commandsLength; i++)
        {
            if (commands[i].isDeleted == false)
            {
                json comm;
                comm["scale"] = commands[i].scale;
                comm["rotationAngle"] = commands[i].rotationAngle;
                comm["commandName"] = commands[i].commandName;
                comm["parameters"] = commands[i].parameters;
                comm["requiresAndOp"] = commands[i].requiresAndOp;
                comm["x"] = commands[i].topLeftCorner.x;
                comm["y"] = commands[i].topLeftCorner.y;
                comm["id"] = commands[i].id;

                comp.push_back(comm);
            }
        }
        data["commands"] = comp;
        auto conn = json::array();
        for (int i = 0; i <= connectionsLength; i++)
        {
            if (connections[i].isDeleted == false)
            {
                json con;
                con["connectionInID"] = connections[i].connectionInID;
                con["connectionOutID"] = connections[i].connectionOutID;

                conn.push_back(con);
            }
        }
        data["connections"] = conn;
        data["biggestID"] = commandId;
        // printf("%s\n", data.dump().c_str());
    }
}

void CommandMaker::draw(sf::RenderWindow &win, sf::Font font)
{
    if (isRunResultScreenVisible)
    {
        runResultContainer.drawCustom(Point(0, 0), 0, 1, win, sf::Color::Black, sf::Color::Black);
        sf::Text resultText;
        resultText.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width * 0.03, sf::VideoMode::getDesktopMode().height * 0.1));
        resultText.setCharacterSize(sf::VideoMode::getDesktopMode().height * 0.03);
        resultText.setFillColor(sf::Color::White);
        resultText.setFont(font);
        resultText.setString(toShowResult);
        int maxRightPos = sf::VideoMode::getDesktopMode().width * 0.97;
        bool isInScreen = false;
        while (!isInScreen)
        {
            bool isAllInScreen = true;
            for (std::string::size_type i = 0; i < toShowResult.size() && isAllInScreen == true; i++)
            {
                if (resultText.findCharacterPos(i).x > maxRightPos)
                {
                    printf("%ld\n", i);
                    toShowResult.insert(i - 2, 1, '\n');
                    resultText.setString(toShowResult);
                    isAllInScreen = false;
                }
            }
            if (isAllInScreen == true)
                isInScreen = true;
        }

        resultText.setString(sf::String::fromUtf8(toShowResult.begin(), toShowResult.end()));
        win.draw(resultText);
    }
    else
    {
        container.drawCustom(Point(0, 0), 0, 1, win, sf::Color::Black, sf::Color::Black);
        for (int i = 0; i <= commandsLength; i++)
            commands[i].draw(win, font);
        for (int i = 0; i < defaultButtonsLength; i++)
            defaultButtons[i].drawCustom(win, font);

        rotationSlider.draw(win, font);
        scaleSlider.draw(win, font);
        quitButton.draw(win, font);
        saveButton.drawCustom(win, font);
        saveAsButton.drawCustom(win, font);
        if (currentSelectedCommandIndex != -1)
        {
            deleteComponent.drawCustom(win, font);
            editComponent.drawCustom(win, font);
        }
        if (isRunnable)
        {
            runCommand.drawCustom(win, font);
            runCommandLocally.drawCustom(win, font);
        }

        for (int i = 0; i <= connectionsLength; i++)
        {
            Point in, out;
            for (int j = 0; j <= commandsLength; j++)
            {
                if (commands[j].id == connections[i].connectionInID)
                {
                    in.x = commands[j].topLeftCorner.x + commands[j].connectionIn.x;
                    in.y = commands[j].topLeftCorner.y + commands[j].connectionIn.y;
                }
                if (commands[j].id == connections[i].connectionOutID)
                {
                    out.x = commands[j].topLeftCorner.x + commands[j].connectionOut.x;
                    out.y = commands[j].topLeftCorner.y + commands[j].connectionOut.y;
                }
            }
            connections[i].draw(in, out, win);
        }

        if (isFromOutConnectionSelected)
        {
            Point in;
            for (int i = 0; i <= commandsLength; i++)
            {
                if (commands[i].id == selectedOutConnectionID)
                {
                    in.x = commands[i].topLeftCorner.x + commands[i].connectionOut.x;
                    in.y = commands[i].topLeftCorner.y + commands[i].connectionOut.y;
                }
            }
            sf::Vertex line1[] =
                {
                    sf::Vertex(sf::Vector2f(in.x, in.y)),
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y))};
            sf::Vertex line2[] =
                {
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y)),
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y))};
            sf::Vertex line3[] =
                {
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y)),
                    sf::Vertex(sf::Vector2f(otherEnd.x, otherEnd.y))};

            win.draw(line1, 2, sf::Lines);
            win.draw(line2, 2, sf::Lines);
            win.draw(line3, 2, sf::Lines);
        }
        if (isFromInConnectionSelected)
        {
            Point in;
            for (int i = 0; i <= commandsLength; i++)
            {
                if (commands[i].id == selectedInConnectionID)
                {
                    in.x = commands[i].topLeftCorner.x + commands[i].connectionIn.x;
                    in.y = commands[i].topLeftCorner.y + commands[i].connectionIn.y;
                }
            }
            sf::Vertex line1[] =
                {
                    sf::Vertex(sf::Vector2f(in.x, in.y)),
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y))};
            sf::Vertex line2[] =
                {
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y)),
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y))};
            sf::Vertex line3[] =
                {
                    sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y)),
                    sf::Vertex(sf::Vector2f(otherEnd.x, otherEnd.y))};

            win.draw(line1, 2, sf::Lines);
            win.draw(line2, 2, sf::Lines);
            win.draw(line3, 2, sf::Lines);
        }
        if (isCommandModalOpened)
            commandModal.draw(win, font);
        if (isSaveAsModalOpened)
            saveAsModal.draw(win, font);
    }
}