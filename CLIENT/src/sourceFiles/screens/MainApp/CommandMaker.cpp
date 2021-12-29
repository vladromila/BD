#include "../../../headers/screens/MainApp/CommandMaker.h"

CommandMaker::CommandMaker()
{
}

CommandMaker::CommandMaker(int clientSocket, json userData) : 
container(Point(0, sf::VideoMode::getDesktopMode().height * 0.1), sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height * 0.9),
c1("ls",Point(500,1080)),
c2("filter",Point(sf::VideoMode::getDesktopMode().width*0.075,200))

{
    this->clientSocket = clientSocket;
    this->userData = userData;
}

void CommandMaker::onMouseMove(sf::Vector2f mousePos)
{
}

void CommandMaker::onMousePress(sf::Vector2f mousePos, sf::RenderWindow &win)
{
}
void CommandMaker::onTextEntered(sf::Event e)
{
}
void CommandMaker::draw(sf::RenderWindow &win, sf::Font font)
{
    container.drawCustom(Point(0, 0), 0, 1, win, sf::Color::Black, sf::Color::Black);
    c1.draw(win,font);
    c2.draw(win,font);

}