#include <SFML/Graphics.hpp>
#include "../../../sourceFiles/subcomponents/TextInput.cpp"
#include "../../../sourceFiles/subcomponents/Button.cpp"

class LoginScreen
{
    TextInput emailAddress;
    TextInput password;
    Button loginButton;
    Button registerButton;
    sf::Texture bgImageTexture;

    sf::Sprite bgImage;
    int clientSocket;

public:
    LoginScreen(int clientSocket);
    void draw(sf::RenderWindow &win);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};