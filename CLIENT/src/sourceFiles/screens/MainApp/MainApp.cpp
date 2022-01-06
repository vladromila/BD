#include "../../../headers/screens/MainApp/MainApp.h"

MainApp::MainApp()
{
}

MainApp::MainApp(int clientSocket) : auth(clientSocket)
{
    logoTexture.loadFromFile("ddp.png");
    logo = sf::Sprite(logoTexture);
    logo.setPosition(9, 9);
    // logo.setScale(1,1);
    logo.setScale((sf::VideoMode::getDesktopMode().height * 0.07 - 9) / 100 - 0.2, sf::VideoMode::getDesktopMode().height * 0.07 / 100 - 0.2);

    this->clientSocket = clientSocket;
    bgImageTexture.loadFromFile("bg.png");
    bgImage = sf::Sprite(bgImageTexture);
    bgImage.setScale(1, 1);

    bgClearImageTexture.loadFromFile("bgClear.jpg");
    bgClearImage = sf::Sprite(bgClearImageTexture);
    bgClearImage.setScale(1, 1);

    std::fstream configFile;
    char homeDir[256];
    strcpy(homeDir, getenv("HOME"));
    strcat(homeDir, "/.config/DDP.json");

    configFile.open(homeDir, std::ios::in);
    if (!configFile)
    {
        printf("Config file could not be opened.");
        screen = 0;
    }
    else
    {
        std::string savedUserData;
        getline(configFile, savedUserData);
        json toSendBody = json::parse(savedUserData);
        toSendBody["reqType"] = "loginWithToken";
        write(clientSocket, toSendBody.dump().c_str(), toSendBody.dump().size() + 1);

        char res[1024];
        read(clientSocket, res, 1024);
        std::string resString;
        resString.append(res);
        json resJson = json::parse(resString);
        if (resJson["isLoggedIn"] == true)
            userData = json::parse(savedUserData), screen = 1;
        else
            screen = 0;
        configFile.close();
    }
    configFile.close();
}

void MainApp::onMouseMove(sf::Vector2f mousePos)
{
    if (screen == 0)
        auth.onMouseMove(mousePos);
    else if (screen == 1)
        menu.onMouseMove(mousePos);
    else if (screen == 2)
        commandMaker.onMouseMove(mousePos);
}

void MainApp::onMouseRightPress(sf::Vector2f mousePos, sf::RenderWindow &win)
{
    if (screen == 2)
    {
        commandMaker.onMouseRightPress(mousePos, win);
    }
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
            screen = 2;
        }
        else if (menuRes == 2)
        {
            send(clientSocket, "exit", 4, 0);
            close(clientSocket);
            win.close();
        }
    }
    else if (screen == 2)
    {
        commandMaker.onMousePress(mousePos, win);
    }
}

void MainApp::onMouseRelease(sf::Vector2f mousePos)
{
    commandMaker.onMouseRelease(mousePos);
}

void MainApp::onTextEntered(sf::Event e)
{
    if (screen == 0)
        auth.onTextEntered(e);
    else if (screen == 2)
        commandMaker.onTextEntered(e);
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
    {
        commandMaker.draw(win, font);
        win.draw(logo);
    }
}