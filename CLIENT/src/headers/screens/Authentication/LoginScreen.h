#include <SFML/Graphics.hpp>
#include "../../../sourceFiles/subcomponents/TextInput.cpp"
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/subcomponents/Word.cpp"

class LoginScreen
{
    Point emailAddressOrigin;
    TextInput emailAddress;
    Point passwordOrigin;
    TextInput password;
    Point loginButtonOrigin;
    Button loginButton;
    Point registerButtonOrigin;
    Button registerButton;
    sf::Texture bgImageTexture;

    Point titleOrigin;
    Word title;

    sf::Sprite bgImage;
    int clientSocket;

public:
    LoginScreen();
    LoginScreen(int clientSocket);
    void draw(sf::RenderWindow &win);
    void onMouseMove(sf::Vector2f mousePos);
    void onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};