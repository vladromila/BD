#include "../../headers/subcomponents/SaveAsModal.h"

SaveAsModal::SaveAsModal()
{
    container = Rectangle(Point((sf::VideoMode().getDesktopMode().width - 700) / 2, sf::VideoMode().getDesktopMode().height * 0.2), 700, sf::VideoMode().getDesktopMode().height * 0.45);
    generalCommandName = TextInput(Point((sf::VideoMode().getDesktopMode().width - 600) / 2, sf::VideoMode().getDesktopMode().height * 0.4), 600, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your command name.", false);

    title.setString("Command name:");
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(sf::VideoMode().getDesktopMode().height * 0.05);
    title.setPosition(sf::Vector2f(sf::VideoMode().getDesktopMode().width / 2, sf::VideoMode().getDesktopMode().height * 0.3));

    mainContainer = sf::RectangleShape(sf::Vector2f(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height));
    mainContainer.setFillColor(sf::Color(0, 0, 0, 150));
    mainContainer.setScale(1, 1);
    mainContainer.setPosition(0, 0);

    saveButton = Button(Point((sf::VideoMode().getDesktopMode().width + 100) / 2, sf::VideoMode::getDesktopMode().height * 0.55), 250, sf::VideoMode::getDesktopMode().height * 0.06, sf::VideoMode::getDesktopMode().height * 0.04, "Save", sf::Color(75, 181, 67), sf::Color(75, 181, 67), sf::Color::White, sf::Color(75, 181, 67), sf::Color::White, sf::Color(75, 181, 67));
    cancelButton = Button(Point((sf::VideoMode().getDesktopMode().width - 600) / 2, sf::VideoMode::getDesktopMode().height * 0.55), 250, sf::VideoMode::getDesktopMode().height * 0.06, sf::VideoMode::getDesktopMode().height * 0.04, "Cancel", sf::Color::Red, sf::Color::Red, sf::Color::White, sf::Color::Red, sf::Color::White, sf::Color::Red);
}

void SaveAsModal::onMouseMove(sf::Vector2f mousePos)
{
    saveButton.onMouseMove(mousePos);
    cancelButton.onMouseMove(mousePos);
}
std::string SaveAsModal::onMousePress(sf::Vector2f mousePos)
{
    generalCommandName.onMousePress(mousePos);
    json res = {{"isCanceled", false}, {"isSaved", false}};
    if (cancelButton.onMousePress(mousePos) == true)
    {
        res["isCanceled"] = true;
        return res.dump();
    }
    if (saveButton.onMousePress(mousePos) == true)
    {
        res["isSaved"] = true;
        return res.dump();
    }
    return res.dump();
}

void SaveAsModal::onTextEntered(sf::Event e)
{
    generalCommandName.onTextEntered(e);
}

void SaveAsModal::draw(sf::RenderWindow &win, sf::Font font)
{
    title.setFont(font);
    sf::FloatRect textRect = title.getLocalBounds();

    title.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
    win.draw(mainContainer);
    container.drawCustom(Point(0, 0), 0, 1, win, sf::Color(192, 192, 192), sf::Color::White);
    generalCommandName.draw(win, font);
    win.draw(title);
    cancelButton.drawCustom(win, font);
    saveButton.drawCustom(win, font);
}