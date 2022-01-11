#include "../../../headers/screens/MainApp/Menu.h"

Menu::Menu() : menuTitleOrigin((sf::VideoMode::getDesktopMode().width) * 0.5, sf::VideoMode::getDesktopMode().height * 0.29),
               menuTitle(menuTitleOrigin, sf::VideoMode::getDesktopMode().height * 0.1, "Menu"),
               newCommandButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.38, sf::VideoMode::getDesktopMode().height * 0.38),
               newCommandButton(newCommandButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.24, sf::VideoMode::getDesktopMode().height * 0.06, sf::VideoMode::getDesktopMode().height * 0.035, "New Command", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White),
               savedCommandsButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.38, sf::VideoMode::getDesktopMode().height * 0.48),
               savedCommandsButton(savedCommandsButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.24, sf::VideoMode::getDesktopMode().height * 0.06, sf::VideoMode::getDesktopMode().height * 0.035, "Saved Commands", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White),
               exitButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.38, sf::VideoMode::getDesktopMode().height * 0.58),
               exitButton(exitButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.24, sf::VideoMode::getDesktopMode().height * 0.06, sf::VideoMode::getDesktopMode().height * 0.035, "Exit", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White),
               profileButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.9-3, 3),
               profileButton(profileButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.10, sf::VideoMode::getDesktopMode().height * 0.06, sf::VideoMode::getDesktopMode().height * 0.035, "Profile", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White)
{
}

void Menu::onMouseMove(sf::Vector2f mousePos)
{
    newCommandButton.onMouseMove(mousePos);
    savedCommandsButton.onMouseMove(mousePos);
    exitButton.onMouseMove(mousePos);
    profileButton.onMouseMove(mousePos);
}

int Menu::onMousePress(sf::Vector2f mousePos)
{
    if (newCommandButton.onMousePress(mousePos) == true)
        return 0;
    else if (savedCommandsButton.onMousePress(mousePos) == true)
        return 1;
    else if (exitButton.onMousePress(mousePos) == true)
        return 2;
    else if (profileButton.onMousePress(mousePos) == true)
        return 3;
    return -1;
}

void Menu::draw(sf::RenderWindow &win, sf::Font font)
{
    menuTitle.draw(win, font);
    newCommandButton.drawCustom(win, font);
    savedCommandsButton.drawCustom(win, font);
    exitButton.drawCustom(win, font);
    profileButton.drawCustom(win,font);
}