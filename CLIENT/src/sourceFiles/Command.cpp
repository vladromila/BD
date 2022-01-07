#include "../headers/Command.h"
#include <bits/stdc++.h>

Command::Command()
{
}
Command::Command(std::string commandName, Point origin, int id)
{
    this->id = id;
    topLeftCorner.changeValues(origin.x, origin.y);
    this->commandName = commandName;

    Point containerOrigin(40 - ((commandName.size()) * 25 + 80) / 2, 5 - INITIAL_COMMAND_HEIGHT / 2);
    container = Rectangle(containerOrigin, (commandName.size()) * 25, INITIAL_COMMAND_HEIGHT - 10);

    connectionIn.changeValues(0 - (container.w + 80) / 2, 0);
    cip.changeValues(0 - (container.w) / 2 - 3, 0);
    connectionOut.changeValues(container.w + 80 - (container.w + 80) / 2, 0);
    cop.changeValues(container.w - (container.w) / 2 + 3, 0);

    Point selectedContainerOrigin(-((commandName.size()) * 25 + 80) / 2, -INITIAL_COMMAND_HEIGHT / 2);
    selectedContainer = Rectangle(selectedContainerOrigin, (commandName.size()) * 25 + 80, INITIAL_COMMAND_HEIGHT);
}

void Command::scaleAt(float scale)
{
    this->scale = scale;
    cip.scalePoint(scale);
    cop.scalePoint(scale);
    connectionIn.scalePoint(scale);
    connectionOut.scalePoint(scale);
    container.topLeftCorner.scalePoint(scale);
    selectedContainer.topLeftCorner.scalePoint(scale);
}

void Command::rotateAt(int rot)
{
    rotationAngle = rot;
    cip.rotatePoint(rot);
    cop.rotatePoint(rot);
    connectionIn.rotatePoint(rot);
    connectionOut.rotatePoint(rot);
    container.topLeftCorner.rotatePoint(rot);
    selectedContainer.topLeftCorner.rotatePoint(rot);
}

bool Command::onMousePress(sf::Vector2f mousePos)
{
    return selectedContainer.isMouseOn(mousePos, topLeftCorner, scale, rotationAngle);
}

void Command::draw(sf::RenderWindow &win, sf::Font font)
{
    if (isDeleted == false)
    {
        if (isSelected == true && isStartCommand == false && isEndCommand == false)
            selectedContainer.drawAsSelected(topLeftCorner, rotationAngle, scale, win);
        if (isEndCommand == true || (isStartCommand == false && isEndCommand == false))
            connectionIn.draw(topLeftCorner, win);
        if (isStartCommand == true || (isStartCommand == false && isEndCommand == false))
            connectionOut.draw(topLeftCorner, win);
        if ((isStartCommand == false && isEndCommand == false))
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

        sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(topLeftCorner.x + cip.x, topLeftCorner.y + cip.y)),
                sf::Vertex(sf::Vector2f(topLeftCorner.x + connectionIn.x, topLeftCorner.y + connectionIn.y))};

        sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(topLeftCorner.x + cop.x, topLeftCorner.y + cop.y)),
                sf::Vertex(sf::Vector2f(topLeftCorner.x + connectionOut.x, topLeftCorner.y + connectionOut.y))};
        win.draw(line1, 2, sf::Lines);
        win.draw(line2, 2, sf::Lines);
        if ((isStartCommand == false && isEndCommand == false))
            win.draw(letterComponent);
    }
}