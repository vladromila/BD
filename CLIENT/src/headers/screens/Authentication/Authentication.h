#include "../../../sourceFiles/screens/Authentication/LoginScreen.cpp"
#include "../../../sourceFiles/screens/Authentication/RegisterScreen.cpp"

class Authentication
{
    LoginScreen loginScreen;
    RegisterScreen registerScreen;
    int selectedScreen = 0;

public:
    Authentication();
    Authentication(int clientSocket);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
    void draw(sf::RenderWindow &win);
};