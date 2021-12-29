#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
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

    Point titleOrigin;
    Word title;

    sf::Sprite bgImage;
    int clientSocket;

public:
    LoginScreen();
    LoginScreen(int clientSocket);
    void draw(sf::RenderWindow &win, sf::Font font);
    void onMouseMove(sf::Vector2f mousePos);
    std::string onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};