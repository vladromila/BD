#include <sstream> // for string streams
#include <string>  // for string
#include <iostream>
#include <SFML/Graphics.hpp>

class Slider
{
    sf::RectangleShape slider;
    sf::RectangleShape axis;
    sf::Text text;
    int minValue;
    int maxValue;
    int xCord;
    int yCord;
    int axisWidth;
    int axisHeight;
    int sliderWidth;
    int sliderHeight;
    float sliderValue;
    bool vertical;

public:
    bool isActivated = false;
    Slider();
    Slider(int x, int y, bool vert);
    sf::Text returnText(int x, int y, std::string z, int fontSize,sf::Font f);
    void create(int min, int max);
    bool isMouseOn(sf::Vector2f mousePos);
    void logic(sf::RenderWindow &window);
    float getSliderValue();
    void setSliderValue(float newValue);
    void draw(sf::RenderWindow &window,sf::Font f);
    void updateSliderPos(int w, int h);
};
