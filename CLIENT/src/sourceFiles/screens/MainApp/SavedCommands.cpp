#include "../../../headers/screens/MainApp/SavedCommands.h"
#include "../../../sourceFiles/subcomponents/SavedCommand.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

SavedCommands::SavedCommands()
{
}

SavedCommands::SavedCommands(int clientSocket, json currentUserData)
{
    this->clientSocket = clientSocket;
    userData = currentUserData;
    Point titleOrigin((sf::VideoMode::getDesktopMode().width) * 0.505, sf::VideoMode::getDesktopMode().height * 0.075);

    title = Word(titleOrigin, sf::VideoMode::getDesktopMode().height * 0.05, "Saved Commands");
    userData = currentUserData;

    json req;
    req["reqType"] = "getUserCommands";
    req["email"] = userData["email"];
    std::string reqStr = std::to_string(req.dump().length() + 1);
    reqStr += '~';
    reqStr += req.dump();
    send(clientSocket, reqStr.c_str(), reqStr.length() + 1, 0);

    char buffer[1024];

    recv(clientSocket, buffer, 1024, 0);
    printf("%s\n", buffer);

    json data = json::parse(buffer);

    for (const auto &item : data["commands"].items())
    {
        commands[commandsLength] = SavedCommand(item.value()["name"], item.value()["id"], commandsLength);
        commandsLength++;
    }
    printf("nr de elemente %d\n", commandsLength);
}

void SavedCommands::onMouseMove(sf::Vector2f mousePos)
{

    for (int i = 0; i < commandsLength; i++)
        commands[i].onMouseMove(mousePos);
}

std::string SavedCommands::onMousePress(sf::Vector2f mousePos)
{
    json fRes = {
        {"selected", false},
        {"switchToMenu", false}};
    if (mousePos.x <= sf::VideoMode().getDesktopMode().width * 0.1 && mousePos.y <= sf::VideoMode().getDesktopMode().height * 0.07)
    {
        fRes["switchToMenu"] = true;
        return fRes.dump();
    }
    else
    {
        for (int i = 0; i < commandsLength; i++)
        {
            if (commands[i].deleteButton.onMousePress(mousePos))
            {
                json req;
                req["reqType"] = "deleteUserCommand";
                req["id"] = commands[i].id;
                req["email"] = userData["email"];
                std::string toSendString = std::to_string(req.dump().length() + 1);
                toSendString += "~";
                toSendString += req.dump();
                send(clientSocket, toSendString.c_str(), toSendString.length(), 0);
                char buffer[10000];
                recv(clientSocket, buffer, 10000, 0);

                json data = json::parse(buffer);
                commandsLength = 0;
                for (const auto &item : data["commands"].items())
                {
                    commands[commandsLength] = SavedCommand(item.value()["name"], item.value()["id"], commandsLength);
                    commandsLength++;
                }
            }
            else if (commands[i].onMousePress(mousePos))
            {
                json req;
                req["reqType"] = "getUserCommand";
                req["id"] = commands[i].id;
                std::string toSendString = std::to_string(req.dump().length() + 1);
                toSendString += "~";
                toSendString += req.dump();
                send(clientSocket, toSendString.c_str(), toSendString.length(), 0);
                char buffer[10000];
                recv(clientSocket, buffer, 10000, 0);
                json resJson = json::parse(buffer);
                json comm;
                comm = json::parse(std::string(resJson["command"]));
                comm["generalCommandId"] = commands[i].id;
                comm["generalCommandName"] = commands[i].title;
                fRes["selected"] = true;
                fRes["command"] = comm;
            }
        }
    }

    return fRes.dump();
}

void SavedCommands::onTextEntered(sf::Event e)
{
}

void SavedCommands::draw(sf::RenderWindow &win, sf::Font font)
{
    title.draw(win, font);
    for (int i = 0; i < commandsLength; i++)
        commands[i].draw(win, font);
}