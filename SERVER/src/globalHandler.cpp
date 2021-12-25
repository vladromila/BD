#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <string>
#include <openssl/sha.h>
#include "/usr/include/mysql/mysql.h"
using json = nlohmann::json;

bool isChar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// Function to check the character
// is an digit or not
bool isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

// Function to check email id is
// valid or not
bool isEmailValid(std::string email)
{
    // Check the first character
    // is an alphabet or not
    if (!isChar(email[0]))
    {

        // If it's not an alphabet
        // email id is not valid
        return 0;
    }
    // Variable to store position
    // of At and Dot
    int At = -1, Dot = -1;

    // Traverse over the email id
    // string to find position of
    // Dot and At
    for (int i = 0;
         i < email.length(); i++)
    {

        // If the character is '@'
        if (email[i] == '@')
        {

            At = i;
        }

        // If character is '.'
        else if (email[i] == '.')
        {

            Dot = i;
        }
    }

    // If At or Dot is not present
    if (At == -1 || Dot == -1)
        return 0;

    // If Dot is present before At
    if (At > Dot)
        return 0;

    // If Dot is present at the end
    return !(Dot >= (email.length() - 1));
}

void sha256_string(const char *string, char outputBuffer[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

std::string login(std::string email, std::string password, MYSQL *con)
{
    char hashedPassword[65];
    sha256_string(password.c_str(), hashedPassword);
    char query[1024];
    int query_stat;
    sprintf(query, "insert into users(firstName,lastName, password) values('%s','%s','%s')", email.c_str(), password.c_str(), hashedPassword);

    query_stat = mysql_query(con, query);

    if (query_stat != 0)
    {
        json res = {
            {"success", false},
            {"generalError", "Error creating a new user. Try again later."}};
        return res.dump();
    }
    else
    {
        json res = {
            {"success", true},
        };
        return res.dump();
    }
}

std::string registerUser(std::string email, std::string password, std::string passwordConfirm, std::string firstName, std::string lastName, MYSQL *con)
{

    json res = {
        {"success", false},
        {"emailError", ""},
        {"firstNameError", ""},
        {"lastNameError", ""},
        {"passwordError", ""},
        {"passwordConfirmError", ""}};

    bool isAnyError = false;
    if (!isEmailValid(email))
    {
        res["emailError"] = "Invalid email address format.";
        isAnyError = true;
    }

    MYSQL_RES *dbRes;
    char initial_query[1024];
    int initial_query_stat;
    // sprintf(initial_query, "SELECT firstName FROM users WHERE firstName='%s'", email.c_str());
    printf("ue incerc sa verifiv daca merge\n");
    mysql_query(con, "SELECT firstName FROM users WHERE firstName='romilavlad2001@gmail.com';");
    dbRes = mysql_store_result(con);
    printf("nr e in plm %" PRIu64 "\n", mysql_num_rows(dbRes));
    if (mysql_num_rows(dbRes))
    {

        res["email"] = "A user with this email address already exists.";
        return res.dump();
    }
    else
        return res.dump();
    printf("a trecut de taote verificarile\n");
    if (firstName.size() < 4)
    {
        res["firstNameError"] = "The first name is too short.";
        isAnyError = true;
    }

    if (lastName.size() < 4)
    {
        res["lastNameError"] = "The last name is too short.";
        isAnyError = true;
    }

    if (password.size() < 4)
    {
        res["passwordError"] = "The entered password is too short.";
        isAnyError = true;
    }

    if (password != passwordConfirm)
    {
        res["passwordConfirmError"] = "The passwords do not match.";
        isAnyError = true;
    }
    if (isAnyError == true)
    {
        return res.dump();
    }

    char hashedPassword[65];
    sha256_string(password.c_str(), hashedPassword);
    char query[1024];
    int query_stat;
    sprintf(query, "insert into users(firstName,lastName, password) values('%s','%s','%s')", firstName.c_str(), lastName.c_str(), hashedPassword);

    query_stat = mysql_query(con, query);

    if (query_stat != 0)
    {

        res["passwordConfirm"] = "Error creating a new user. Try again later.";
        return res.dump();
    }

    else
    {
        res["success"] = true;
        return res.dump();
    }
}

std::string requestHandler(char *r, MYSQL *con)
{
    std::string request;
    request.append(r);
    json req = json::parse(request, nullptr, true);
    if (req.is_discarded())
    {
        std::string res = "rip";
        return res;
    }
    else
    {
        if (req["reqType"] == "login")
            return login(req["email"], req["password"], con);
        else if (req["reqType"] == "register")
            return registerUser(req["email"], req["password"], req["passwordConfirm"], req["firstName"], req["lastName"], con);
    }
}
