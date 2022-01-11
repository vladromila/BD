#include <SFML/Graphics.hpp>
#include "../../../sourceFiles/subcomponents/TextInput.cpp"
#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/subcomponents/Word.cpp"

class EditProfile
{
    TextInput emailAddress;
    TextInput firstName;
    TextInput lastName;
    TextInput password;
    TextInput passwordConfirm;
    Button editButton;
    Button logoutButton;

    Word title;

    int clientSocket;
    json userData;

public:
    EditProfile();
    EditProfile(int clientSocket, json userData);
    void draw(sf::RenderWindow &win, sf::Font font);
    void onMouseMove(sf::Vector2f mousePos);
    std::string onMousePress(sf::Vector2f mousePos);
    void onTextEntered(sf::Event e);
};