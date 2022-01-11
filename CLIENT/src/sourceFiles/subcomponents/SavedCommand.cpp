#ifndef SavedCommand_H
#define SavedCommand_H

#include "../../headers/subcomponents/SavedCommand.h"

SavedCommand::SavedCommand()
{
}

SavedCommand::SavedCommand(std::string title, std::string id, int i)
{
    fontColor = sf::Color(79, 61, 194);
    fontColorHover = sf::Color::White;
    fill = sf::Color::White;
    fillHover = sf::Color(79, 61, 194);
    container = Rectangle(Point(0, 0), sf::VideoMode().getDesktopMode().width * 0.9, sf::VideoMode().getDesktopMode().height * 0.05);

    deleteButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.85, (sf::VideoMode().getDesktopMode().height * (0.05) + 10) * (i + 2)), (sf::VideoMode::getDesktopMode().width) * 0.10, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "Delete", sf::Color::Red, sf::Color::Red, sf::Color::White, sf::Color::Red, sf::Color::White, sf::Color::Red);

    this->topLeftCorner = Point(sf::VideoMode().getDesktopMode().width * 0.05 - 3, (sf::VideoMode().getDesktopMode().height * (0.05) + 10) * (i + 2));
    this->fontSize = fontSize;
    this->title = title;
    this->id = id;
    btnTextComponent.setString(title);
    btnTextComponent.setCharacterSize(sf::VideoMode().getDesktopMode().height * 0.035);
    btnTextComponent.setPosition(sf::Vector2f(sf::VideoMode().getDesktopMode().width * 0.07, (sf::VideoMode().getDesktopMode().height * (0.05) + 10) * (i + 2) + sf::VideoMode().getDesktopMode().height * 0.006));
}

void SavedCommand::onMouseMove(sf::Vector2f mousePos)
{
    if (container.isMouseOn(mousePos, topLeftCorner, 1, 0) == true)
        isHovered = true;
    else
        isHovered = false;
    deleteButton.onMouseMove(mousePos);
}

bool SavedCommand::onMousePress(sf::Vector2f mousePos)
{
    if (container.isMouseOn(mousePos, topLeftCorner, 1, 0) == true)
        return true;
    else
        return false;
}

void SavedCommand::draw(sf::RenderWindow &win, sf::Font font)
{
    if (isHovered)
        container.drawCustom(topLeftCorner, 0, 1, win, fillHover, fillHover);
    else
        container.drawCustom(topLeftCorner, 0, 1, win, fill, fill);

    if (isHovered)
        btnTextComponent.setFillColor(fontColorHover);
    else
        btnTextComponent.setFillColor(fontColor);
    btnTextComponent.setFont(font);
    deleteButton.drawCustom(win, font);

    win.draw(btnTextComponent);
}

#endif