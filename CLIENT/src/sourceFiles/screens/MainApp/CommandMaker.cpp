#include "../../../headers/screens/MainApp/CommandMaker.h"

CommandMaker::CommandMaker()
{
}

CommandMaker::CommandMaker(int clientSocket, json userData) : container(Point(sf::VideoMode::getDesktopMode().width * 0.1 + 9, sf::VideoMode::getDesktopMode().height * 0.1), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.9), rotationSlider(sf::VideoMode::getDesktopMode().width - 250, sf::VideoMode::getDesktopMode().height - 30, 0), scaleSlider(sf::VideoMode::getDesktopMode().width - 50, sf::VideoMode::getDesktopMode().height - 160, 1)
{
    rotationSlider.create(0, 360);
    scaleSlider.create(3, 8);

    defaultButtons[0] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.1), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cat", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[1] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.15 + 9), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "grep", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[2] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.2 + 18), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "filter", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[3] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.25 + 27), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ls", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[4] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.3 + 36), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[5] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.35 + 45), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "echo", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[6] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.4 + 54), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "pwd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[7] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.45 + 63), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ps", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[8] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.5 + 72), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "touch", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

    this->clientSocket = clientSocket;
    this->userData = userData;
}

void CommandMaker::onMouseMove(sf::Vector2f mousePos)
{
    if (rotationSlider.isActivated == true)
        if (currentSelectedCommandIndex != -1)
            commands[currentSelectedCommandIndex].rotateAt(rotationSlider.getSliderValue());
    if (scaleSlider.isActivated == true)
        if (currentSelectedCommandIndex != -1)
            commands[currentSelectedCommandIndex].scaleAt(scaleSlider.getSliderValue() / 4.0f);
    if (isMouseLongPressed == true && currentSelectedCommandIndex != -1 && rotationSlider.isActivated == false && scaleSlider.isActivated == false)
    {
        commands[currentSelectedCommandIndex].topLeftCorner.x = mousePos.x - xDiffOnLongPress;
        commands[currentSelectedCommandIndex].topLeftCorner.y = mousePos.y - yDiffOnLongPress;
    }
    for (int i = 0; i < defaultButtonsLength; i++)
        defaultButtons[i].onMouseMove(mousePos);
}

void CommandMaker::onMousePress(sf::Vector2f mousePos)
{
    isMouseLongPressed = true;

    bool isACommandSelected = false;
    int commandSelectedIndex = -1;
    bool isOnRotationSlider = rotationSlider.isMouseOn(mousePos);
    bool isOnScaleSlider = scaleSlider.isMouseOn(mousePos);

    for (int i = 0; i <= commandsLength; i++)
        if (commands[i].onMousePress(mousePos))
            isACommandSelected = true, commandSelectedIndex = i;
    if (selectedToAddCommand != "")
    {
        if (isACommandSelected == false)
        {
            if (mousePos.x > sf::VideoMode::getDesktopMode().width * 0.1 + 100 && mousePos.y > sf::VideoMode::getDesktopMode().height * 0.1 + 20 && isOnScaleSlider == false && isOnRotationSlider == false)
            {
                if (currentSelectedCommandIndex != -1)
                {
                    commands[currentSelectedCommandIndex].isSelected = false;
                    currentSelectedCommandIndex = -1;
                }
                commandsLength++;
                currentSelectedCommandIndex = commandsLength;
                commands[commandsLength] = Command(selectedToAddCommand, Point(mousePos.x, mousePos.y));
                xDiffOnLongPress = 0;
                yDiffOnLongPress = 0;
            }
            else if (currentSelectedCommandIndex != -1)
            {
                if (isOnRotationSlider == false && isOnScaleSlider == false)
                {
                    commands[currentSelectedCommandIndex].isSelected = false;
                    currentSelectedCommandIndex = -1;
                }
            }
        }
        else
        {
            if (currentSelectedCommandIndex != commandSelectedIndex)
            {
                commands[currentSelectedCommandIndex].isSelected = false;
                commands[commandSelectedIndex].isSelected = true;
                currentSelectedCommandIndex = commandSelectedIndex;
            }

            yDiffOnLongPress = mousePos.y - commands[commandSelectedIndex].topLeftCorner.y;
            xDiffOnLongPress = mousePos.x - commands[commandSelectedIndex].topLeftCorner.x;
        }
    }
    else if (isACommandSelected == true)
    {
        if (commandSelectedIndex != currentSelectedCommandIndex)
            commands[currentSelectedCommandIndex].isSelected = false, currentSelectedCommandIndex = commandSelectedIndex;
        commands[commandSelectedIndex].isSelected = true;
        yDiffOnLongPress = mousePos.y - commands[commandSelectedIndex].topLeftCorner.y;
        xDiffOnLongPress = mousePos.x - commands[commandSelectedIndex].topLeftCorner.x;
    }
    else
    {
        if (currentSelectedCommandIndex != -1)
            if (isOnScaleSlider == true || isOnRotationSlider == true)
            {
                if (isOnRotationSlider)
                    commands[currentSelectedCommandIndex].rotateAt(rotationSlider.getSliderValue());
                if (isOnScaleSlider)
                    commands[currentSelectedCommandIndex].scaleAt(scaleSlider.getSliderValue() / 4.0f);
            }
            else
                commands[currentSelectedCommandIndex].isSelected = false, currentSelectedCommandIndex = -1;
    }
    if (isACommandSelected == false)
        for (int i = 0; i < defaultButtonsLength; i++)
            if (defaultButtons[i].onMousePress(mousePos))
                if (defaultButtons[i].isSelected == false)
                {
                    for (int j = 0; j < defaultButtonsLength; j++)
                        defaultButtons[j].isSelected = false;
                    defaultButtons[i].isSelected = true;
                    selectedToAddCommand = std::string(defaultButtons[i].btnText);
                }
                else
                    defaultButtons[i].isSelected = false, selectedToAddCommand = "";
}

void CommandMaker::onMouseRelease(sf::Vector2f mousePos)
{
    isMouseLongPressed = false;
    if (rotationSlider.isActivated == true)
        rotationSlider.isActivated = false;
    if (scaleSlider.isActivated == true)
        scaleSlider.isActivated = false;
}

void CommandMaker::onTextEntered(sf::Event e)
{
}

void CommandMaker::draw(sf::RenderWindow &win, sf::Font font)
{
    container.drawCustom(Point(0, 0), 0, 1, win, sf::Color::Black, sf::Color::Black);
    for (int i = 0; i <= commandsLength; i++)
        commands[i].draw(win, font);
    for (int i = 0; i < defaultButtonsLength; i++)
        defaultButtons[i].drawCustom(win, font);

    rotationSlider.draw(win, font);
    scaleSlider.draw(win, font);
}