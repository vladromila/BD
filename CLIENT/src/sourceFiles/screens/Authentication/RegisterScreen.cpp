#include "../../../headers/screens/Authentication/RegisterScreen.h"
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

RegisterScreen::RegisterScreen(int clientSocket)
{
    this->clientSocket = clientSocket;
    Point emailAdressOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.30);
    emailAddress = TextInput(emailAdressOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your email address.", false);

    Point firstNameOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.38);
    firstName = TextInput(firstNameOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your first name.", true);

    Point lastNameOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.46);
    lastName = TextInput(lastNameOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your last name.", false);

    Point passwordOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.54);
    password = TextInput(passwordOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your password.", true);

    Point passwordConfirmOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.2, sf::VideoMode::getDesktopMode().height * 0.62);
    passwordConfirm = TextInput(passwordConfirmOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Confirm the password.", false);

    Point registerButtonOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.45, sf::VideoMode::getDesktopMode().height * 0.70);
    registerButton = Button(registerButtonOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.1, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.03, "Register");
    Point loginButtonOrigin((sf::VideoMode::getDesktopMode().width - 100) * 0.46, sf::VideoMode::getDesktopMode().height * 0.76);
    loginButton = Button(loginButtonOrigin, (sf::VideoMode::getDesktopMode().width - 100) * 0.08, sf::VideoMode::getDesktopMode().height * 0.03, sf::VideoMode::getDesktopMode().height * 0.023, "Login");
    bgImageTexture.loadFromFile("bg.png");

    bgImage = sf::Sprite(bgImageTexture);
    bgImage.setScale(1, 1);
}

void RegisterScreen::onMouseMove(sf::Vector2f mousePos)
{
    loginButton.onMouseMove(mousePos);
    registerButton.onMouseMove(mousePos);
}

void RegisterScreen::onMousePress(sf::Vector2f mousePos)
{
    if (registerButton.onMousePress(mousePos) == true)
    {
        std::string email(emailAddress.getInputValue());
        std::string fn(firstName.getInputValue());
        std::string ln(lastName.getInputValue());
        std::string pass(password.getInputValue());

        json reqBody = {
            {"reqType", "login"},
            {"email", email},
            {"firstName",fn},
            {"lastName",ln},
            {"password", pass}};

        std::string reqStr=reqBody.dump();
        write(clientSocket,reqStr.c_str(),reqBody.dump().size()+1);
        char res[1024];
        bzero(res, 1024);
        read(clientSocket, res, 1024);
        printf("%s\n", res);
    }
    if (loginButton.onMousePress(mousePos) == true)
    {
    }
    emailAddress.onMousePress(mousePos);
    password.onMousePress(mousePos);
}

void RegisterScreen::onTextEntered(sf::Event e)
{
    emailAddress.onTextEntered(e);
    password.onTextEntered(e);
}

void RegisterScreen::draw(sf::RenderWindow &win)
{
    win.draw(bgImage);
    emailAddress.draw(win);
    firstName.draw(win);
    lastName.draw(win);
    password.draw(win);
    passwordConfirm.draw(win);

    loginButton.draw(win);
    registerButton.draw(win);
}