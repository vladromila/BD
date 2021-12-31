#include "../headers/Command.h"
#include <bits/stdc++.h>

Command::Command()
{
}
Command::Command(std::string commandName, Point origin)
{
    isSelected=true;
    topLeftCorner.changeValues(origin.x, origin.y);
    this->commandName = commandName;

    Point containerOrigin(40 - ((commandName.size()) * 20 + 80) / 2, 5 - INITIAL_COMMAND_HEIGHT / 2);
    container = Rectangle(containerOrigin, (commandName.size()) * 20, INITIAL_COMMAND_HEIGHT - 10);

    connectionIn.changeValues(0 - (container.w + 80) / 2, 0);
    connectionOut.changeValues(container.w + 80 - (container.w + 80) / 2, 0);

    Point selectedContainerOrigin(-((commandName.size()) * 20 + 80) / 2, -INITIAL_COMMAND_HEIGHT / 2);
    selectedContainer = Rectangle(selectedContainerOrigin, (commandName.size()) * 20 + 80, INITIAL_COMMAND_HEIGHT);
}

void Command::scaleAt(float scale)
{
    this->scale = scale;
    connectionIn.scalePoint(scale);
    connectionOut.scalePoint(scale);
    container.topLeftCorner.scalePoint(scale);
    selectedContainer.topLeftCorner.scalePoint(scale);
}

void Command::rotateAt(int rot)
{
    rotationAngle = rot;
    connectionIn.rotatePoint(rot);
    connectionOut.rotatePoint(rot);
    container.topLeftCorner.rotatePoint(rot);
    selectedContainer.topLeftCorner.rotatePoint(rot);
}

bool Command::onMousePress(sf::Vector2f mousePos)
{
    return selectedContainer.isMouseOn(mousePos, topLeftCorner);
}

void Command::draw(sf::RenderWindow &win, sf::Font font)
{
    if (isSelected == true)
        selectedContainer.drawAsSelected(topLeftCorner, rotationAngle, scale, win);
    connectionIn.draw(topLeftCorner, win);
    connectionOut.draw(topLeftCorner, win);
    container.draw(topLeftCorner, rotationAngle, scale, win);
    letterComponent.setFont(font);
    letterComponent.setRotation(rotationAngle);
    letterComponent.setCharacterSize(30 * scale);
    letterComponent.setString(commandName);
    letterComponent.setFillColor(sf::Color::White);
    if (hasSetOrigin == false)
        initialLetterX = letterComponent.getGlobalBounds().width / 2;
    letterComponent.setOrigin(initialLetterX * scale, (INITIAL_COMMAND_HEIGHT / 2 - 5) * scale), hasSetOrigin = true;
    letterComponent.setPosition(topLeftCorner.x, topLeftCorner.y);

    win.draw(letterComponent);
}