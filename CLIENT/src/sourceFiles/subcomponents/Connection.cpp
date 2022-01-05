
#include "../../headers/subcomponents/Connection.h"

Connection::Connection()
{
}

void Connection::draw(Point connectionInID, Point connectionOutID, sf::RenderWindow &win)
{
    if (isDeleted == false)
    {
        sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(connectionInID.x, connectionInID.y)),
                sf::Vertex(sf::Vector2f(connectionInID.x + (connectionOutID.x - connectionInID.x) / 2, connectionInID.y))};
        sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(connectionInID.x + (connectionOutID.x - connectionInID.x) / 2, connectionInID.y)),
                sf::Vertex(sf::Vector2f(connectionInID.x + (connectionOutID.x - connectionInID.x) / 2, connectionOutID.y))};
        sf::Vertex line3[] =
            {
                sf::Vertex(sf::Vector2f(connectionInID.x + (connectionOutID.x - connectionInID.x) / 2, connectionOutID.y)),
                sf::Vertex(sf::Vector2f(connectionOutID.x, connectionOutID.y))};

        win.draw(line1, 2, sf::Lines);
        win.draw(line2, 2, sf::Lines);
        win.draw(line3, 2, sf::Lines);
    }
}