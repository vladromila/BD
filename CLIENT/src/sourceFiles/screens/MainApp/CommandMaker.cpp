#include "../../../headers/screens/MainApp/CommandMaker.h"

CommandMaker::CommandMaker()
{
}

CommandMaker::CommandMaker(int clientSocket, json userData) : container(Point(sf::VideoMode::getDesktopMode().width * 0.1 + 9, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.93),
                                                              rotationSlider(sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().width * 0.05 - 250, sf::VideoMode::getDesktopMode().height - 30, 0),
                                                              scaleSlider(sf::VideoMode::getDesktopMode().width - 50, sf::VideoMode::getDesktopMode().height - sf::VideoMode::getDesktopMode().height * 0.05 - 160, 1)
{
      rotationSlider.create(0, 360);
    scaleSlider.create(3, 8);

    saveButton= Button(Point(sf::VideoMode::getDesktopMode().width * 0.1+9, 3), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.07-9, sf::VideoMode::getDesktopMode().height * 0.045, "Save", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
        saveAsButton= Button(Point(sf::VideoMode::getDesktopMode().width * 0.20+18, 3), sf::VideoMode::getDesktopMode().width * 0.14, sf::VideoMode::getDesktopMode().height * 0.07-9, sf::VideoMode::getDesktopMode().height * 0.045, "Save As", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);


    quitButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.975 - 9, sf::VideoMode::getDesktopMode().height * 0.95 - 6), sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.031, "X");

    defaultButtons[0] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.07), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cat", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[1] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.12 + 9), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "grep", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[2] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.17 + 18), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "filter", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[3] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.22 + 27), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ls", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[4] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.27 + 36), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "cd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[5] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.32 + 45), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "echo", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[6] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.37 + 54), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "pwd", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[7] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.42 + 63), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "ps", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);
    defaultButtons[8] = Button(Point(3, sf::VideoMode::getDesktopMode().height * 0.47 + 72), sf::VideoMode::getDesktopMode().width * 0.1, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "touch", sf::Color::White, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, sf::Color(79, 61, 194), sf::Color::White, true);

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
    quitButton.onMouseMove(mousePos);
    if (isFromInConnectionSelected || isFromOutConnectionSelected)
    {
        otherEnd.x = mousePos.x;
        otherEnd.y = mousePos.y;
    }
}

void CommandMaker::onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win)
{
    printf("%d\n", connectionsLength);
    isMouseLongPressed = true;

    bool isACommandSelected = false;
    int commandSelectedIndex = -1;
    bool isOnRotationSlider = rotationSlider.isMouseOn(mousePos);
    bool isOnScaleSlider = scaleSlider.isMouseOn(mousePos);

    for (int i = 0; i <= commandsLength; i++)
        if (commands[i].onMousePress(mousePos))
            isACommandSelected = true, commandSelectedIndex = i;
    for (int i = 0; i <= commandsLength; i++)
    {
        if (commands[i].connectionIn.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
        {
            bool isAlreadyConnected = false;
            for (int j = 0; j <= connectionsLength; j++)
                if (connections[j].isDeleted == false && connections[j].connectionInID == commands[i].id)
                {
                    isFromOutConnectionSelected = true;
                    selectedOutConnectionID = connections[j].connectionOutID;
                    connections[j].isDeleted = true;
                    isAlreadyConnected = true;
                }
            if (isAlreadyConnected == false)
            {
                isFromInConnectionSelected = true;
                selectedInConnectionID = commands[i].id;
            }
        }
        if (isFromInConnectionSelected == true)
        {
            isFromOutConnectionSelected = false;
            selectedOutConnectionID = -1;
        }
        else if (isFromOutConnectionSelected == false)
        {
            if (commands[i].connectionOut.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
            {
                bool isAlreadyConnected = false;
                for (int j = 0; j <= connectionsLength; j++)
                    if (connections[j].isDeleted == false && connections[j].connectionOutID == commands[i].id)
                    {
                        isFromInConnectionSelected = true;
                        selectedInConnectionID = connections[j].connectionInID;
                        connections[j].isDeleted = true;
                        isAlreadyConnected = true;
                    }
                if (isAlreadyConnected == false)
                {
                    isFromOutConnectionSelected = true;
                    selectedOutConnectionID = commands[i].id;
                }
            }
        }
    }
    if (isFromOutConnectionSelected || isFromInConnectionSelected)
    {
        for (int i = 0; i <= commandsLength; i++)
            commands[i].isSelected = false;
        currentSelectedCommandIndex = -1;
        otherEnd.x = mousePos.x;
        otherEnd.y = mousePos.y;
    }
    else if (selectedToAddCommand != "")
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
                commands[commandsLength] = Command(selectedToAddCommand, Point(mousePos.x, mousePos.y), ++commandId);
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
    if (quitButton.onMousePress(mousePos))
    {
        send(clientSocket, "exit", 4, 0);
        close(clientSocket);
        win.close();
    }
}

void CommandMaker::onMouseRelease(sf::Vector2f mousePos)
{
    isMouseLongPressed = false;
    if (rotationSlider.isActivated == true)
        rotationSlider.isActivated = false;
    if (scaleSlider.isActivated == true)
        scaleSlider.isActivated = false;

    for (int i = 0; i <= commandsLength; i++)
    {
        if (isFromInConnectionSelected)
        {
            if (commands[i].connectionOut.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
            {
                if (selectedInConnectionID != commands[i].id)
                {
                    bool isAlreadyConnected = false;
                    for (int j = 0; j <= connectionsLength; j++)
                        if (connections[j].isDeleted == true && connections[j].connectionInID == selectedInConnectionID && connections[j].connectionOutID == commands[i].id)
                        {
                            isAlreadyConnected = true;
                            connections[j].isDeleted = false;
                        }
                    if (isAlreadyConnected == false)
                    {
                        connections[++connectionsLength].connectionInID = selectedInConnectionID;
                        connections[connectionsLength].connectionOutID = commands[i].id;
                    }
                }
            }
        }
        if (isFromOutConnectionSelected)
        {
            if (commands[i].connectionIn.isMouseOn(commands[i].topLeftCorner, Point(mousePos.x, mousePos.y)))
            {
                if (selectedOutConnectionID != commands[i].id)
                {
                    bool isAlreadyConnected = false;
                    for (int j = 0; j <= connectionsLength; j++)
                        if (connections[j].isDeleted == true && connections[j].connectionInID == commands[i].id && connections[j].connectionOutID == selectedOutConnectionID)
                        {
                            isAlreadyConnected = true;
                            connections[j].isDeleted = false;
                        }
                    if (isAlreadyConnected == false)
                    {
                        connections[++connectionsLength].connectionInID = commands[i].id;
                        connections[connectionsLength].connectionOutID = selectedOutConnectionID;
                    }
                }
            }
        }
    }

    selectedOutConnectionID = -1;
    selectedInConnectionID = -1;
    isFromOutConnectionSelected = false;
    isFromInConnectionSelected = false;
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
    quitButton.draw(win, font);
    saveButton.drawCustom(win,font);
    saveAsButton.drawCustom(win,font);
    for (int i = 0; i <= connectionsLength; i++)
    {
        Point in, out;
        for (int j = 0; j <= commandsLength; j++)
        {
            if (commands[j].id == connections[i].connectionInID)
            {
                in.x = commands[j].topLeftCorner.x + commands[j].connectionIn.x;
                in.y = commands[j].topLeftCorner.y + commands[j].connectionIn.y;
            }
            if (commands[j].id == connections[i].connectionOutID)
            {
                out.x = commands[j].topLeftCorner.x + commands[j].connectionOut.x;
                out.y = commands[j].topLeftCorner.y + commands[j].connectionOut.y;
            }
        }
        connections[i].draw(in, out, win);
    }

    if (isFromOutConnectionSelected)
    {
        Point in;
        for (int i = 0; i <= commandsLength; i++)
        {
            if (commands[i].id == selectedOutConnectionID)
            {
                in.x = commands[i].topLeftCorner.x + commands[i].connectionOut.x;
                in.y = commands[i].topLeftCorner.y + commands[i].connectionOut.y;
            }
        }
        sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(in.x, in.y)),
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y))};
        sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y)),
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y))};
        sf::Vertex line3[] =
            {
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y)),
                sf::Vertex(sf::Vector2f(otherEnd.x, otherEnd.y))};

        win.draw(line1, 2, sf::Lines);
        win.draw(line2, 2, sf::Lines);
        win.draw(line3, 2, sf::Lines);
    }
    if (isFromInConnectionSelected)
    {
        Point in;
        for (int i = 0; i <= commandsLength; i++)
        {
            if (commands[i].id == selectedInConnectionID)
            {
                in.x = commands[i].topLeftCorner.x + commands[i].connectionIn.x;
                in.y = commands[i].topLeftCorner.y + commands[i].connectionIn.y;
            }
        }
        sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(in.x, in.y)),
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y))};
        sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, in.y)),
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y))};
        sf::Vertex line3[] =
            {
                sf::Vertex(sf::Vector2f(in.x + (otherEnd.x - in.x) / 2, otherEnd.y)),
                sf::Vertex(sf::Vector2f(otherEnd.x, otherEnd.y))};

        win.draw(line1, 2, sf::Lines);
        win.draw(line2, 2, sf::Lines);
        win.draw(line3, 2, sf::Lines);
    }
}