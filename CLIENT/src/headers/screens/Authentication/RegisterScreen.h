#include <SFML/Graphics.hpp>
#include "../../../sourceFiles/subcomponents/TextInput.cpp"
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/subcomponents/Word.cpp"

class RegisterScreen
{
    TextInput emailAddress;
    TextInput firstName;
    TextInput lastName;
    TextInput password;
    TextInput passwordConfirm;
    Button loginButton;
    Button registerButton;
    sf::Texture bgImageTexture;

    Word title;

    sf::Sprite bgImage;
    int clientSocket;

public:
RegisterScreen();
    RegisterScreen(int clientSocket);
    void draw(sf::RenderWindow &win);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};