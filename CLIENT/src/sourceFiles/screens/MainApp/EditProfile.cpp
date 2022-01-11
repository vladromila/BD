#include "../../../headers/screens/MainApp/EditProfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

EditProfile::EditProfile()
{
}

EditProfile::EditProfile(int clientSocket, json currentUserData)
{
    this->clientSocket = clientSocket;
    Point emailAdressOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.30);
    emailAddress = TextInput(emailAdressOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your email address.", false);
    strcpy(emailAddress.input, std::string(currentUserData["email"]).c_str());

    Point firstNameOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.39);
    firstName = TextInput(firstNameOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your first name.", false);
    strcpy(firstName.input, std::string(currentUserData["firstName"]).c_str());

    Point lastNameOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.48);
    lastName = TextInput(lastNameOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your last name.", false);
    strcpy(lastName.input, std::string(currentUserData["lastName"]).c_str());

    Point passwordOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.57);
    password = TextInput(passwordOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Enter your password.", true);

    Point passwordConfirmOrigin((sf::VideoMode::getDesktopMode().width) * 0.2, sf::VideoMode::getDesktopMode().height * 0.66);
    passwordConfirm = TextInput(passwordConfirmOrigin, (sf::VideoMode::getDesktopMode().width) * 0.6, sf::VideoMode::getDesktopMode().height * 0.05, sf::VideoMode::getDesktopMode().height * 0.035, "Confirm the password.", true);

    Point editButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.45, sf::VideoMode::getDesktopMode().height * 0.75);
    editButton = Button(editButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.1, sf::VideoMode::getDesktopMode().height * 0.04, sf::VideoMode::getDesktopMode().height * 0.025, "Edit");
    Point logoutButtonOrigin((sf::VideoMode::getDesktopMode().width) * 0.46, sf::VideoMode::getDesktopMode().height * 0.81);
    logoutButton = Button(logoutButtonOrigin, (sf::VideoMode::getDesktopMode().width) * 0.08, sf::VideoMode::getDesktopMode().height * 0.03, sf::VideoMode::getDesktopMode().height * 0.01875, "Log out");

    Point titleOrigin((sf::VideoMode::getDesktopMode().width) * 0.505, sf::VideoMode::getDesktopMode().height * 0.24);

    title = Word(titleOrigin, sf::VideoMode::getDesktopMode().height * 0.08, "Edit profile");
    userData = currentUserData;
}

void EditProfile::onMouseMove(sf::Vector2f mousePos)
{
    editButton.onMouseMove(mousePos);
    logoutButton.onMouseMove(mousePos);
}

std::string EditProfile::onMousePress(sf::Vector2f mousePos)
{
    json fRes = {
        {"edited", false},
        {"switchToLogin", false},
        {"switchToMenu", false}};
    if (mousePos.x <= sf::VideoMode().getDesktopMode().width * 0.1 && mousePos.y <= sf::VideoMode().getDesktopMode().height * 0.07)
    {
        fRes["switchToMenu"]=true;
        return fRes.dump();
    }

    emailAddress.onMousePress(mousePos);
    password.onMousePress(mousePos);
    passwordConfirm.onMousePress(mousePos);
    firstName.onMousePress(mousePos);
    lastName.onMousePress(mousePos);
    if (editButton.onMousePress(mousePos) == true)
    {
        emailAddress.resetError();
        firstName.resetError();
        lastName.resetError();
        password.resetError();
        passwordConfirm.resetError();

        std::string email(emailAddress.getInputValue());
        std::string fn(firstName.getInputValue());
        std::string ln(lastName.getInputValue());
        std::string pass(password.getInputValue());
        std::string passc(passwordConfirm.getInputValue());
        json reqBody = {
            {"reqType", "updateUser"},
            {"email", email},
            {"oldEmail", userData["email"]},
            {"firstName", fn},
            {"lastName", ln},
            {"password", pass},
            {"passwordConfirm", passc}};

        std::string reqStr = std::to_string(reqBody.dump().length() + 1);
        reqStr += '~';
        reqStr += reqBody.dump();
        send(clientSocket, reqStr.c_str(), reqStr.length() + 1, 0);
        char res[1024];
        bzero(res, 1024);
        read(clientSocket, res, 1024);
        std::string resString;
        resString.append(res);
        json resJson = json::parse(resString);
        // printf("%s \n", resJson.dump().c_str());
        if (resJson["success"] == true)
        {
            fRes["edited"] = true;
            fRes["data"]["email"] = email;
            fRes["data"]["firstName"] = fn;
            fRes["data"]["lastName"] = ln;
            fRes["data"]["session_token"] = userData["session_token"];
            std::fstream configFile;
            char homeDir[256];
            strcpy(homeDir, getenv("HOME"));
            strcat(homeDir, "/.config/DDP.json");

            configFile.open(homeDir, std::ios::out);
            if (!configFile)
            {
                printf("Config file could not be opened.");
            }
            configFile << fRes["data"].dump().c_str();
            configFile.close();
            return fRes.dump();
        }
        else
        {
            emailAddress.changeError(resJson["emailError"]);
            firstName.changeError(resJson["firstNameError"]);
            lastName.changeError(resJson["lastNameError"]);
            password.changeError(resJson["passwordError"]);
            passwordConfirm.changeError(resJson["passwordConfirmError"]);
        }
    }
    if (logoutButton.onMousePress(mousePos) == true)
    {
        fRes["switchToLogin"] = true;
        std::fstream configFile;
        char homeDir[256];
        strcpy(homeDir, getenv("HOME"));
        strcat(homeDir, "/.config/DDP.json");

        configFile.open(homeDir, std::ios::out);
        if (!configFile)
        {
            printf("Config file could not be opened.");
        }
        userData["session_token"]="";
        configFile << userData.dump().c_str();
        configFile.close();
        return fRes.dump();
    }
    return fRes.dump();
}

void EditProfile::onTextEntered(sf::Event e)
{
    emailAddress.onTextEntered(e);
    firstName.onTextEntered(e);
    lastName.onTextEntered(e);
    password.onTextEntered(e);
    passwordConfirm.onTextEntered(e);
}

void EditProfile::draw(sf::RenderWindow &win, sf::Font font)
{
    emailAddress.draw(win, font);
    firstName.draw(win, font);
    lastName.draw(win, font);
    password.draw(win, font);
    passwordConfirm.draw(win, font);

    editButton.draw(win, font);
    logoutButton.draw(win, font);
    title.draw(win, font);
}