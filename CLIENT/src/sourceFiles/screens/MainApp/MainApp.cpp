#include "../../../headers/screens/MainApp/MainApp.h"

MainApp::MainApp()
{
}

MainApp::MainApp(int clientSocket) : auth(clientSocket)
{
    this->clientSocket = clientSocket;
    bgImageTexture.loadFromFile("bg.png");
    bgImage = sf::Sprite(bgImageTexture);
    bgImage.setScale(1, 1);

    bgClearImageTexture.loadFromFile("bgClear.jpg");
    bgClearImage = sf::Sprite(bgClearImageTexture);
    bgClearImage.setScale(1, 1);
}

void MainApp::onMouseMove(sf::Vector2f mousePos)
{
    if (screen == 0)
        auth.onMouseMove(mousePos);
    else if (screen == 1)
        menu.onMouseMove(mousePos);
}

void MainApp::onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win)
{
    if (screen == 0)
    {
        std::string authRes = auth.onMousePress(mousePos);
        json authResJson = json::parse(authRes);
        if (authResJson["loggedIn"] == true)
        {
            userData = authResJson["data"];
            screen = 1;
        }
    }
    else if (screen == 1)
    {
        int menuRes = menu.onMousePress(mousePos);
        if (menuRes == 0)
        {
            commandMaker = CommandMaker(clientSocket, userData);
            screen=2;
        }
        else if (menuRes == 2)
        {
            send(clientSocket, "exit", 4, 0);
            close(clientSocket);
            win.close();
        }
    }
}
void MainApp::onTextEntered(sf::Event e)
{
    if (screen == 0)
        auth.onTextEntered(e);
}
void MainApp::draw(sf::RenderWindow &win, sf::Font font)
{
    if (screen == 0)
        win.draw(bgImage);
    else
        win.draw(bgClearImage);
    if (screen == 0)
        auth.draw(win, font);
    else if (screen == 1)
        menu.draw(win, font);
    else if (screen == 2)
        commandMaker.draw(win, font);
}