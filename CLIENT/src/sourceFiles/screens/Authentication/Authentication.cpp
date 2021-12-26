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

void Authentication::onMousePress(sf::Vector2f mousePos)
{
    if (selectedScreen == 1)
        loginScreen.onMousePress(mousePos);
    else
        registerScreen.onMousePress(mousePos);
}

void Authentication::onTextEntered(sf::Event e)
{
    if (selectedScreen == 1)
        loginScreen.onTextEntered(e);
    else
        registerScreen.onTextEntered(e);
}

void Authentication::draw(sf::RenderWindow &win)
{
    if (selectedScreen == 1)
    {
        loginScreen.draw(win);
    }
    else
        registerScreen.draw(win);
}