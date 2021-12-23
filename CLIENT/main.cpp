#include <SFML/Graphics.hpp>
#include "./src/sourceFiles/LoginScreen.cpp"
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Client Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    int W = sf::VideoMode::getDesktopMode().width;
    int H = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(W, H), "DDP by Romila Vlad Alexandru", sf::Style::Fullscreen);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Point commandOrigin(W * .125, 550);
    int rot = 0;
    LoginScreen loginScreen(clientSocket);
    while (window.isOpen())
    {

        window.clear();
        sf::Event event;

        while (window.pollEvent(event))
        {
            sf::Vector2i mousePos;
            mousePos = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                rot += 10;
            }
            if (event.type == sf::Event::Resized)
            {
                // sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                // window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::TextEntered)
            {
                loginScreen.onTextEntered(event);
            }
            if (event.type == sf::Event::MouseMoved)
            {
                loginScreen.onMouseMove(sf::Vector2f(mousePos));
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                loginScreen.onMousePress(sf::Vector2f(mousePos));
            }
        }
        loginScreen.draw(window);
        window.display();
    }

    return 0;
}
