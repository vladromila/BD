#include <SFML/Graphics.hpp>
#include "./src/sourceFiles/Command.cpp"
#include "./src/sourceFiles/subcomponents/TextInput.cpp"
#include<bits/stdc++.h>
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    int W = sf::VideoMode::getDesktopMode().width - 100;
    int H = sf::VideoMode::getDesktopMode().height - 100;
    sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!",sf::Style::Default);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Point commandOrigin(W*.125, 550);
    int rot = 0;
    Command c("filter", commandOrigin);

    TextInput t(commandOrigin,"Enter your email address.");
    while (window.isOpen())
    {

        window.clear();
        sf::Event event;
        sf::Vector2i mousePos;
        mousePos = sf::Mouse::getPosition(window);
        sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(0, 0)),
                sf::Vertex(sf::Vector2f(mousePos.x / 2, 0))};
        sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(0 + (mousePos.x) / 2, 0)),
                sf::Vertex(sf::Vector2f(0 + (mousePos.x) / 2, mousePos.y))};
        sf::Vertex line3[] =
            {
                sf::Vertex(sf::Vector2f(0 + (mousePos.x - 0) / 2, mousePos.y)),
                sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y))};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                rot += 10;
                c.rotate(rot);
                t.onClick(sf::Vector2f(mousePos));
            }
            if(event.type==sf::Event::Resized)
            {
                    // sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    // window.setView(sf::View(visibleArea));
            }
            if(event.type==sf::Event::TextEntered)
            {
                t.onTextEntered(event);
            }
        }
        t.draw(window);
        window.display();
    }

    return 0;
}
