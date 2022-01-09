#include "../../headers/subcomponents/CommandModal.h"

CommandModal::CommandModal()
{
    container = Rectangle(Point(sf::VideoMode().getDesktopMode().width * 0.15, sf::VideoMode().getDesktopMode().height * 0.2), sf::VideoMode().getDesktopMode().width * 0.7, sf::VideoMode().getDesktopMode().height * 0.55);
    parameters = TextInput(Point(sf::VideoMode().getDesktopMode().width * 0.19, sf::VideoMode().getDesktopMode().height * 0.4), (sf::VideoMode::getDesktopMode().width) * 0.62 - 9, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter the command parameters", false);

    title.setString("Parameters:");
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(sf::VideoMode().getDesktopMode().height * 0.05);
    title.setPosition(sf::Vector2f(sf::VideoMode().getDesktopMode().width / 2, sf::VideoMode().getDesktopMode().height * 0.3));

    mainContainer = sf::RectangleShape(sf::Vector2f(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height));
    mainContainer.setFillColor(sf::Color(0, 0, 0, 150));
    mainContainer.setScale(1, 1);
    mainContainer.setPosition(0, 0);

    saveButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.66, sf::VideoMode::getDesktopMode().height * 0.65), (sf::VideoMode::getDesktopMode().width) * 0.15, sf::VideoMode::getDesktopMode().height * 0.07, sf::VideoMode::getDesktopMode().height * 0.045, "Save", sf::Color(75, 181, 67), sf::Color(75, 181, 67), sf::Color::White, sf::Color(75, 181, 67), sf::Color::White, sf::Color(75, 181, 67));
    closeButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.47, sf::VideoMode::getDesktopMode().height * 0.65), (sf::VideoMode::getDesktopMode().width) * 0.15, sf::VideoMode::getDesktopMode().height * 0.07, sf::VideoMode::getDesktopMode().height * 0.045, "Close", sf::Color::Blue, sf::Color::Blue, sf::Color::White, sf::Color::Blue, sf::Color::White, sf::Color::Blue);
    deleteButton = Button(Point(sf::VideoMode::getDesktopMode().width * 0.19, sf::VideoMode::getDesktopMode().height * 0.65), (sf::VideoMode::getDesktopMode().width) * 0.24, sf::VideoMode::getDesktopMode().height * 0.07, sf::VideoMode::getDesktopMode().height * 0.045, "Delete Component", sf::Color::Red, sf::Color::Red, sf::Color::White, sf::Color::Red, sf::Color::White, sf::Color::Red);
    requiredAndOp = Button(Point(sf::VideoMode::getDesktopMode().width * 0.375, sf::VideoMode::getDesktopMode().height * 0.5), (sf::VideoMode::getDesktopMode().width) * 0.25, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.03, "Requires AND operator", sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Blue, sf::Color(75, 181, 67), sf::Color::White, true);
}

void CommandModal::onMouseMove(sf::Vector2f mousePos)
{
    deleteButton.onMouseMove(mousePos);
    closeButton.onMouseMove(mousePos);
    saveButton.onMouseMove(mousePos);
    requiredAndOp.onMouseMove(mousePos);
}
std::string CommandModal::onMousePress(sf::Vector2f mousePos)
{
    if (requiredAndOp.onMousePress(mousePos))
    {
        requiredAndOp.isSelected = !requiredAndOp.isSelected;
    }
    json res = {{"save", false}, {"delete", false}, {"close", false}};
    parameters.onMousePress(mousePos);
    if (saveButton.onMousePress(mousePos))
        res["save"] = true, res["command"] = std::string(parameters.getInputValue());
    if (deleteButton.onMousePress(mousePos))
        res["delete"] = true;
    if (closeButton.onMousePress(mousePos))
        res["close"] = true;
    return res.dump();
}

void CommandModal::onTextEntered(sf::Event e)
{
    parameters.onTextEntered(e);
}

void CommandModal::draw(sf::RenderWindow &win, sf::Font font)
{
    title.setFont(font);
    sf::FloatRect textRect = title.getLocalBounds();

    title.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
    win.draw(mainContainer);
    container.drawCustom(Point(0, 0), 0, 1, win, sf::Color(192, 192, 192), sf::Color::White);
    parameters.draw(win, font);
    win.draw(title);
    requiredAndOp.drawCustom(win, font);
    deleteButton.drawCustom(win, font);
    saveButton.drawCustom(win, font);
    closeButton.drawCustom(win, font);
}