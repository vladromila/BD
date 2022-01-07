#include "../../../headers/screens/MainApp/MainApp.h"

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(const std::string &data)
{
    std::array<unsigned char, 4> char_array;
    std::string ret;

    for (auto begin = data.begin(), end = data.end(), it = begin; it != end; ++it)
    {
        if (!is_base64(*it))
            break;

        auto index = it - begin;

        char_array[index % char_array.size()] = *it;

        if (index % char_array.size() != char_array.size() - 1)
            continue;

        for (auto &character : char_array)
            character = static_cast<unsigned char>(base64_chars.find(character));

        ret += (char_array[0] << 2) + ((char_array[1] & 0x30) >> 4);
        ret += ((char_array[1] & 0xf) << 4) + ((char_array[2] & 0x3c) >> 2);
        ret += ((char_array[2] & 0x3) << 6) + char_array[3];
    }

    return ret;
}

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
        std::string toSendString = std::to_string(toSendBody.dump().length() + 1);
        toSendString += '~';
        toSendString += toSendBody.dump();
        printf("%s %d\n", toSendString.c_str(), toSendString.length() + 1);
        send(clientSocket, toSendString.c_str(), toSendString.length() + 1, 0);

        char res[1024];
        recv(clientSocket, res, 1024, 0);
        printf("%s\n", res);
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
    //  win.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "DDP by Romila Vlad Alexandru", sf::Style::Default);
    //             win.clear();
    //             char filename[1024];
    //             FILE *f = popen("zenity --file-selection", "r");
    //             fgets(filename, 1024, f);
    //             win.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "DDP by Romila Vlad Alexandru", sf::Style::Fullscreen);

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
            commandMaker = CommandMaker(clientSocket, userData, "{\"biggestID\":1,\"commands\":[{\"parameters\":\"\", \"commandName\":\"cp\",\"id\":2,\"rotationAngle\":0,\"scale\":1.0,\"x\":1463,\"y\":417}],\"connections\":[{\"connectionInID\":2,\"connectionOutID\":0},{\"connectionInID\":1,\"connectionOutID\":2}]}");
            screen = 2;
        }
        else if (menuRes == 2)
        {
            send(clientSocket, "5~exit", 6, 0);
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