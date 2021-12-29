#include "../../../headers/screens/Authentication/Authentication.h"

Authentication::Authentication()
{
}

Authentication::Authentication(int cS) : loginScreen(cS), registerScreen(cS)
{
}

void Authentication::onMouseMove(sf::Vector2f mousePos)
{
    if (selectedScreen == 1)
        loginScreen.onMouseMove(mousePos);
    else
        registerScreen.onMouseMove(mousePos);
}

std::string Authentication::onMousePress(sf::Vector2f mousePos)
{
    if (selectedScreen == 1)
    {
        std::string loginPressStatus = loginScreen.onMousePress(mousePos);
        printf("%s\n",loginPressStatus.c_str());
        json loginPressStatusJson = json::parse(loginPressStatus);
        if (loginPressStatusJson["switchToRegister"] == true)
            selectedScreen = 0;
        return loginPressStatus;
    }
    else
    {
        std::string registerPressStatus = registerScreen.onMousePress(mousePos);
        printf("%s\n",registerPressStatus.c_str());
        json registerPressStatusJson = json::parse(registerPressStatus);
        if (registerPressStatusJson["switchToLogin"] == true)
            selectedScreen = 1;
        return registerPressStatus;
    }
}

void Authentication::onTextEntered(sf::Event e)
{
    if (selectedScreen == 1)
        loginScreen.onTextEntered(e);
    else
        registerScreen.onTextEntered(e);
}

void Authentication::draw(sf::RenderWindow &win, sf::Font font)
{
    if (selectedScreen == 1)
    {
        loginScreen.draw(win, font);
    }
    else
        registerScreen.draw(win, font);
}