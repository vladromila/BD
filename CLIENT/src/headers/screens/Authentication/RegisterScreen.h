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

    Word title;

    int clientSocket;

public:
    RegisterScreen();
    RegisterScreen(int clientSocket);
    void draw(sf::RenderWindow &win,sf::Font font);
    void onMouseMove(sf::Vector2f mousePos);
    std::string onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};