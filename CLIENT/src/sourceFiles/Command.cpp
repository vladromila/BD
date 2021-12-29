#include "../headers/Command.h"
#include <bits/stdc++.h>

Command::Command()
{
}
Command::Command(std::string commandName, Point origin)
{
    topLeftCorner.changeValues(origin.x, origin.y);
    this->commandName = commandName;

    Point containerOrigin(40 - ((commandName.size() + 2) * 20 + 80) / 2, 5 - INITIAL_COMMAND_HEIGHT / 2);
    container = Rectangle(containerOrigin, (commandName.size() + 2) * 20, INITIAL_COMMAND_HEIGHT - 10);

container.topLeftCorner.scalePoint(scale);
    connectionIn.changeValues(0 - (container.w + 80) / 2, 0);
    connectionOut.changeValues(container.w + 80 - (container.w + 80) / 2, 0);
    connectionIn.scalePoint(scale);
    connectionOut.scalePoint(scale);
}
void Command::rotate(int rot)
{
    rotationAngle = rot;
    connectionIn.rotatePoint(rot);
    connectionOut.rotatePoint(rot);
    container.topLeftCorner.rotatePoint(rot);
}
void Command::draw(sf::RenderWindow &win, sf::Font font)
{
    connectionIn.draw(topLeftCorner, win);
    connectionOut.draw(topLeftCorner, win);
    container.draw(topLeftCorner, rotationAngle, scale, win);
    sf::Text letterComponent;
    letterComponent.setFont(font);
    letterComponent.rotate(rotationAngle);
    letterComponent.setCharacterSize(30 * scale);
    letterComponent.setString(commandName);
    letterComponent.setFillColor(sf::Color::White);
    letterComponent.setPosition(topLeftCorner.x - (letterComponent.getGlobalBounds().width) / 2, topLeftCorner.y - letterComponent.getGlobalBounds().height / 2-10*scale);
    win.draw(letterComponent);
}