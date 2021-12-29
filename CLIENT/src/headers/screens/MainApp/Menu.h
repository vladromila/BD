#include "../../../sourceFiles/subcomponents/Button.cpp"
#include "../../../sourceFiles/subcomponents/Word.cpp"

class Menu{
    Point newCommandButtonOrigin;
    Button newCommandButton;
    Point savedCommandsButtonOrigin;
    Button savedCommandsButton;
    Point exitButtonOrigin;
    Button exitButton;
    Point menuTitleOrigin;
    Word menuTitle;
public:
    Menu();
    void onMouseMove(sf::Vector2f mousePos);
    int onMousePress(sf::Vector2f mousePos);
    void draw(sf::RenderWindow &win, sf::Font font);
};