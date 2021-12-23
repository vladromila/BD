#include "../headers/LoginScreen.h"
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

#define PORT 4448

LoginScreen::LoginScreen(int clientSocket)
{
    this->clientSocket = clientSocket;
    Point emailAdressOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.35);
    emailAddress = TextInput(emailAdressOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your email address.", false);
    Point passwordOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.43);
    password = TextInput(passwordOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your password.", true);
    Point loginButtonOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.45, sf::VideoMode::getDesktopMode().height * 0.52);
    loginButton = Button(loginButtonOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.1, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.03, "Log In");
    Point registerButtonOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.46, sf::VideoMode::getDesktopMode().height * 0.58);
    registerButton = Button(registerButtonOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.08, sf::VideoMode::getDesktopMode().height * 0.03, sf::VideoMode::getDesktopMode().height * 0.023, "Register");
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
    if (loginButton.onMousePress(mousePos) == true)
    {
        std::string email = "asd";
        // email.append(emailAddress.getInputValue());
        std::string pass = "Asd";
        // pass.append(password.getInputValue());
        json reqBody = {
            {"reqType", "login"},
            {"email", email},
            {"password", pass}};
        write(clientSocket, reqBody.dump().c_str(), 51);
        char res[1024];
        bzero(res, 1024);
        read(clientSocket, res, 1024);
        printf("%s\n", res);
    }
    if (registerButton.onMousePress(mousePos) == true)
    {
    }
    emailAddress.onMousePress(mousePos);
    password.onMousePress(mousePos);
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
}