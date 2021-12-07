#include "../../headers/subcomponents/TextInput.h"

TextInput::TextInput()
{
}
TextInput::TextInput(Point topLeftCorner, const char placeholder[])
{
    this->topLeftCorner.x = topLeftCorner.x;
    this->topLeftCorner.y = topLeftCorner.y;
    int W = (sf::VideoMode::getDesktopMode().width - 100) * 0.75;
    Point containerOrigin(0, 0);
    container = Rectangle(containerOrigin, W, 50);
    container.isTextInputContainer = true;
    strcpy(this->placeholder, placeholder);
    strcpy(input, "_");
    font.loadFromFile("font.ttf");
}

void TextInput::onClick(sf::Vector2f mousePos)
{
    if (container.isMouseOn(mousePos, topLeftCorner) == true)
        isSelected = true;
    else
        isSelected = false;
}

void TextInput::onTextEntered(sf::Event e)
{
    if (isSelected)
    {
        int charTyped = e.text.unicode;

        // Only allow normal inputs:
        if (charTyped < 128)
        {
            if (charTyped == DELETE_KEY)
            {
                if (strlen(input) > 1)
                {
                    input[strlen(input) - 2] = '_';
                    input[strlen(input) - 1] = '\0';
                }
            }
            else
            {

                input[strlen(input) - 1] = tolower(char(charTyped));
                strcat(input, "_");
            }
        }
    }
}
void TextInput::draw(sf::RenderWindow &win)
{
    if (isSelected)
        container.drawAsSelected(topLeftCorner, 0, 1, win);
    else
        container.draw(topLeftCorner, 0, 1, win);
    sf::Text inputComponent;
    inputComponent.setPosition(topLeftCorner.x + 20, topLeftCorner.y + 5);
    inputComponent.setCharacterSize(30);
    if (strcmp(input, "_") == 0 && isSelected == false)
        inputComponent.setString(placeholder);
    else
        inputComponent.setString(input);
    inputComponent.setFillColor(sf::Color::Black);
    inputComponent.setFont(font);
    win.draw(inputComponent);
}