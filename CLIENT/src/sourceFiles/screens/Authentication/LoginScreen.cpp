#include "../../../headers/screens/Authentication/LoginScreen.h"
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

LoginScreen::LoginScreen()
{
}

LoginScreen::LoginScreen(int clientSocket) : titleOrigin((sf::VideoMode::getDesktopMode().width) * 0.5, sf::VideoMode::getDesktopMode().height * 0.29),
                                             title(titleOrigin, sf::VideoMode::getDesktopMode().height * 0.08, "Login"),
                                             emailAddressOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.35),
                                             emailAddress(emailAddressOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your email address.", false),
                                             passwordOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.44),
                                             password(passwordOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your password.", true),
                                             loginButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.45, sf::VideoMode::getDesktopMode().height * 0.53),
                                             loginButton(loginButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.1, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.025, "Login"),
                                             registerButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.46, sf::VideoMode::getDesktopMode().height * 0.59),
                                             registerButton(registerButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.08, sf::VideoMode::getDesktopMode().height * 0.03, sf::VideoMode::getDesktopMode().height * 0.01875, "Register")

{
    this->clientSocket = clientSocket;
}

void LoginScreen::onMouseMove(sf::Vector2f mousePos)
{
    loginButton.onMouseMove(mousePos);
    registerButton.onMouseMove(mousePos);
}

std::string LoginScreen::onMousePress(sf::Vector2f mousePos)
{

    json fRes = {
        {"loggedIn", false},
        {"switchToRegister", false}};
    emailAddress.onMousePress(mousePos);
    password.onMousePress(mousePos);

    if (loginButton.onMousePress(mousePos) == true)
    {

        emailAddress.resetError();
        password.resetError();

        std::string email(emailAddress.getInputValue());
        std::string pass(password.getInputValue());

        json reqBody = {
            {"reqType", "login"},
            {"email", email},
            {"password", pass}};

        std::string reqStr = std::to_string(reqBody.dump().length() + 1);
        reqStr += '~';
        reqStr += reqBody.dump();
        printf("%s\n", reqStr.c_str());
        send(clientSocket, reqStr.c_str(), reqStr.length() + 1, 0);
        char res[1024];
        bzero(res, 1024);
        recv(clientSocket, res, 1024, 0);
        std::string resString;
        resString.append(res);
        json resJson = json::parse(resString);
        // printf("%s\n", resJson.dump().c_str());
        if (resJson["success"] == true)
        {
            std::fstream configFile;
            char homeDir[256];
            strcpy(homeDir, getenv("HOME"));
            strcat(homeDir, "/.config/DDP.json");

            configFile.open(homeDir, std::ios::out);
            if (!configFile)
            {
                printf("Config file could not be opened.");
            }
            configFile << resJson["data"].dump().c_str();
            configFile.close();
            bzero(homeDir, 0);
            fRes["loggedIn"] = true;
            fRes["data"] = resJson["data"];
            return fRes.dump();
        }
        else
        {
            emailAddress.changeError(resJson["emailError"]);
            password.changeError(resJson["passwordError"]);
        }
    }
    if (registerButton.onMousePress(mousePos) == true)
    {
        fRes["switchToRegister"] = true;
        return fRes.dump();
    }
    return fRes.dump();
}

void LoginScreen::onTextEntered(sf::Event e)
{
    emailAddress.onTextEntered(e);
    password.onTextEntered(e);
}

void LoginScreen::draw(sf::RenderWindow &win, sf::Font font)
{
    emailAddress.draw(win, font);
    password.draw(win, font);

    loginButton.draw(win, font);
    registerButton.draw(win, font);
    title.draw(win, font);
}