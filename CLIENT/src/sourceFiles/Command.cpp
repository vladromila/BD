#include "../headers/Command.h"
#include <bits/stdc++.h>
Command::Command(const char *commandName, Point origin)
{
    topLeftCorner.changeValues(origin.x, origin.y);
    strcpy(this->commandName, commandName);

    Point containerOrigin(40-(strlen(this->commandName) * 20+80)/2, 5-INITIAL_COMMAND_HEIGHT/2);
    container = Rectangle(containerOrigin, strlen(this->commandName) * 20, INITIAL_COMMAND_HEIGHT - 10);

    connectionIn.changeValues(0-(container.w+80)/2, 0);
    connectionOut.changeValues(container.w + 80-(container.w+80)/2, 0);
    font.loadFromFile("./src/utils/fonts/OpenSans-Regular.ttf");
}
void Command::rotate(int rot)
{
    rotationAngle = rot;
    connectionIn.rotatePoint(rot);
    connectionOut.rotatePoint(rot);
    container.topLeftCorner.rotatePoint(rot);
}
void Command::draw(sf::RenderWindow &win)
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
    letterComponent.setPosition(topLeftCorner.x + (container.w - letterComponent.getLocalBounds().width) / 2 + 40, topLeftCorner.y);
}