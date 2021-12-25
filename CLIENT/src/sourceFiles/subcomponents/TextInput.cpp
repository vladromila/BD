#include "../../headers/subcomponents/TextInput.h"

TextInput::TextInput()
{
}
TextInput::TextInput(Point topLeftCorner, int w, int h, int fontSize, const char placeholder[], bool securedTextEntry)
{
    this->topLeftCorner.x = topLeftCorner.x;
    this->topLeftCorner.y = topLeftCorner.y;
    isSecuredTextEntry = securedTextEntry;
    width = w;
    height = h;
    Point containerOrigin(0, 0);
    container = Rectangle(containerOrigin, width, height);
    container.isTextInputContainer = true;
    strcpy(this->placeholder, placeholder);
    strcpy(input, "");
    font.loadFromFile("font.ttf");
    this->fontSize = fontSize;
}

void TextInput::onMousePress(sf::Vector2f mousePos)
{
    if (container.isMouseOn(mousePos, topLeftCorner) == true)
    {
        isSelected = true;
        if (hasAddedIndicator == false)
        {
            strcat(input, "_");
            hasAddedIndicator = true;
            hasRemovedIndicator = false;
        }
    }
    else
    {
        isSelected = false;
        if (strlen(input) > 0 && input[strlen(input) - 1] == '_')
            if (hasRemovedIndicator == false)
            {
                input[strlen(input) - 1] = '\0';
                hasRemovedIndicator = true;
                hasAddedIndicator = false;
            }
    }
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
                if (char(charTyped) != '\n')
                {
                    input[strlen(input) - 1] = char(charTyped);
                    strcat(input, "_");
                }
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
    inputComponent.setPosition(topLeftCorner.x + 20, topLeftCorner.y + (height - fontSize) * 0.35);
    inputComponent.setCharacterSize(fontSize);
    if (strcmp(input, "") == 0 && isSelected == false)
        inputComponent.setString(placeholder);
    else if (isSecuredTextEntry)
    {
        char securedStr[100];
        strcpy(securedStr, input);
        for (int i = 0; i < strlen(securedStr) - 1; i++)
        {
            securedStr[i] = '*';
        }
        if (!isSelected)
            securedStr[strlen(securedStr) - 1] = '*';
        inputComponent.setString(securedStr);
    }
    else
        inputComponent.setString(input);
    inputComponent.setFillColor(sf::Color::Black);
    inputComponent.setFont(font);
    win.draw(inputComponent);

    sf::Text errorMessageComponent;
    errorMessageComponent.setPosition(topLeftCorner.x, topLeftCorner.y + height + fontSize / 5);
    errorMessageComponent.setCharacterSize(fontSize / 2);

    errorMessageComponent.setString(errorMessage);
    errorMessageComponent.setFillColor(sf::Color::Red);
    errorMessageComponent.setFont(font);

    errorMessageComponent.setFillColor(sf::Color::Red);
    errorMessageComponent.setFont(font);
    win.draw(errorMessageComponent);
}

char *TextInput::getInputValue()
{
    if (isSelected)
    {
        char *cp;
        strcpy(cp, input);
        cp[strlen(cp) - 1] = '\0';
        return cp;
    }
    else
        return input;
}

void TextInput::resetError()
{
    errorMessage = "";
}

void TextInput::changeError(std::string err)
{
    errorMessage = err;
}