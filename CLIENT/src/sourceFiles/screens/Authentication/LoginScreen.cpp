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

LoginScreen::LoginScreen(int clientSocket) : emailAddressOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.30),
                                             emailAddress(emailAddressOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your email address.", false), passwordOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.57),
                                             password(passwordOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your password.", true),
                                             registerButtonOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.45, sf::VideoMode::getDesktopMode().height * 0.75), registerButton(registerButtonOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.1, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.03, "Register"), loginButtonOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.46, sf::VideoMode::getDesktopMode().height * 0.81),
                                             loginButton(loginButtonOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.08, sf::VideoMode::getDesktopMode().height * 0.03, sf::VideoMode::getDesktopMode().height * 0.023, "Login"), titleOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.505, sf::VideoMode::getDesktopMode().height * 0.24), title(titleOrigin, sf::VideoMode::getDesktopMode().height * 0.08, "Register")
{
    this->clientSocket = clientSocket;

    bgImageTexture.loadFromFile("bg.png");

    bgImage = sf::Sprite(bgImageTexture);
    bgImage.setScale(1, 1);
}

void LoginScreen::onMouseMove(sf::Vector2f mousePos)
{
    loginButton.onMouseMove(mousePos);
    registerButton.onMouseMove(mousePos);
}

void LoginScreen::onMousePress(sf::Vector2f mousePos)
{
    emailAddress.onMousePress(mousePos);
    password.onMousePress(mousePos);
    if (registerButton.onMousePress(mousePos) == true)
    {
        emailAddress.resetError();
        password.resetError();

        std::string email(emailAddress.getInputValue());
        std::string pass(password.getInputValue());
        json reqBody = {
            {"reqType", "register"},
            {"email", email},
            {"password", pass},
        };

        std::string reqStr = reqBody.dump();
        write(clientSocket, reqStr.c_str(), reqBody.dump().size() + 1);
        char res[1024];
        bzero(res, 1024);
        read(clientSocket, res, 1024);
        std::string resString;
        resString.append(res);
        json resJson = json::parse(resString);
        printf("%s \n", resJson.dump().c_str());
        if (resJson["success"] == true)
        {
        }
        else
        {
            emailAddress.changeError(resJson["emailError"]);
            password.changeError(resJson["passwordError"]);
        }
    }
    if (loginButton.onMousePress(mousePos) == true)
    {
    }
}

void LoginScreen::onTextEntered(sf::Event e)
{
    emailAddress.onTextEntered(e);
    password.onTextEntered(e);
}

void LoginScreen::draw(sf::RenderWindow &win)
{
    win.draw(bgImage);
    emailAddress.draw(win);
    password.draw(win);

    loginButton.draw(win);
    registerButton.draw(win);
    title.draw(win);
}