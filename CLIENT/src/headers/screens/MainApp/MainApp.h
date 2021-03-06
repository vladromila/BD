#include "../../../sourceFiles/screens/Authentication/Authentication.cpp"
#include "../../../sourceFiles/screens/MainApp/Menu.cpp"
#include "../../../sourceFiles/screens/MainApp/CommandMaker.cpp"
#include "../../../sourceFiles/screens/MainApp/EditProfile.cpp"
#include "../../../sourceFiles/screens/MainApp/SavedCommands.cpp"


class MainApp
{
    Authentication auth;
    Menu menu;
    CommandMaker commandMaker;
    EditProfile editProfile;
    SavedCommands savedCommands;

    int clientSocket;
    int screen = -1;

    json userData;

    sf::Texture bgImageTexture;

    sf::Sprite bgImage;

    sf::Texture bgClearImageTexture;

    sf::Sprite bgClearImage;

    sf::Sprite logo;
    sf::Texture logoTexture;

public:
    MainApp();
    MainApp(int clientSocket);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win);
    void onMouseRightPress(sf::Vector2f mousePos, sf::RenderWindow &win);
    void onMouseRelease(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
    void draw(sf::RenderWindow &win, sf::Font font);
};