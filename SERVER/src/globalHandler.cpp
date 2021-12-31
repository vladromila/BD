#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <string>
#include <openssl/sha.h>
#include "/usr/include/mysql/mysql.h"
#include <time.h>
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

    json res = {
        {"success", false},
        {"emailError", ""},
        {"passwordError", ""},
        {"session_token", ""},
        {"lastName", ""}};
    bool isAnyError = false;
    if (!isEmailValid(email))
    {
        res["emailError"] = "Invalid email address format.";
        isAnyError = true;
    }
    else
    {
        MYSQL_RES *dbRes;
        char initial_query[1024];
        int initial_query_stat;
        sprintf(initial_query, "SELECT email,password,firstName,lastName FROM users WHERE email='%s'", email.c_str());

        mysql_query(con, initial_query);
        dbRes = mysql_store_result(con);

        if (!mysql_num_rows(dbRes))
        {
            res["emailError"] = "A user with this email does not exist.";
            return res.dump();
        }

        char hashedPassword[65];
        sha256_string(password.c_str(), hashedPassword);

        MYSQL_ROW row = mysql_fetch_row(dbRes);

        if (strcmp(row[1], hashedPassword) != 0)
        {
            res["passwordError"] = "Wrong password. Please try again";
            mysql_free_result(dbRes);
            return res.dump();
        }
        res["data"]["firstName"] = std::string(row[2]);
        res["data"]["lastName"] = std::string(row[3]);
        mysql_free_result(dbRes);
    }

    if (password.size() < 4)
    {
        res["passwordError"] = "The entered password is too short.";
        isAnyError = true;
    }

    if (isAnyError == true)
    {
        return res.dump();
    }

    time_t _tm = time(NULL);

    struct tm *curtime = localtime(&_tm);
    char sessionTokenFrom[100];
    strcpy(sessionTokenFrom, email.c_str());
    strcat(sessionTokenFrom, asctime(curtime));

    char sessionToken[65];
    sha256_string(sessionTokenFrom, sessionToken);

    char query[1024];
    int query_stat;

    sprintf(query, "UPDATE users SET session_token='%s', expiry_date=DATE_ADD(CURDATE(),INTERVAL 1 MONTH) where email='%s'", sessionToken, email.c_str());

    query_stat = mysql_query(con, query);

    if (query_stat != 0)
    {
        res["data"] = "";
        res["password"] = "Error updating the user session. Try again later.";
        return res.dump();
    }
    else
    {
        res["data"]["email"] = email;
        res["data"]["session_token"] = std::string(sessionToken);
        res["success"] = true;
        return res.dump();
    }
}

std::string registerUser(std::string email, std::string password, std::string passwordConfirm, std::string firstName, std::string lastName, MYSQL *con)
{
    printf("am intrat \n");
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
    else
    {
        MYSQL_RES *dbRes;
        char initial_query[1024];
        int initial_query_stat;
        sprintf(initial_query, "SELECT email FROM users WHERE email='%s'", email.c_str());

        mysql_query(con, initial_query);
        dbRes = mysql_store_result(con);

        if (mysql_num_rows(dbRes))
        {
            res["emailError"] = "A user with this email address already exists.";
            return res.dump();
        }
    }
    printf("am trecut de verificarea existentei adresei\n");
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

    time_t _tm = time(NULL);

    struct tm *curtime = localtime(&_tm);
    char *sessionTokenFrom;
    strcpy(sessionTokenFrom, email.c_str());
    strcat(sessionTokenFrom, asctime(curtime));

    char sessionToken[65];
    sha256_string(sessionTokenFrom, sessionToken);

    char hashedPassword[65];
    sha256_string(password.c_str(), hashedPassword);
    char query[1024];
    int query_stat;
    sprintf(query, "insert into users(email,firstName,lastName, password, session_token,expiry_date) values('%s','%s','%s','%s','%s',DATE_ADD(CURDATE(),INTERVAL 1 MONTH))", email.c_str(), firstName.c_str(), lastName.c_str(), hashedPassword, sessionToken);

    query_stat = mysql_query(con, query);
    if (query_stat != 0)
    {
        res["passwordConfirm"] = "Error creating a new user. Try again later.";
        return res.dump();
    }
    else
    {
        res["session_token"] = std::string(sessionToken);
        res["success"] = true;
        return res.dump();
    }
}

std::string loginWithToken(std::string email, std::string session_token, MYSQL *con)
{
    json res = {
        {"isLoggedIn", false}};
    char query[1024];
    int query_stat;

    MYSQL_RES *dbRes;

    sprintf(query, "SELECT email FROM users WHERE email='%s' AND session_token='%s' AND CURDATE()<=expiry_date", email.c_str(), session_token.c_str());
    printf("%s\n", query);
    query_stat = mysql_query(con, query);

    dbRes = mysql_store_result(con);
    if (query_stat != 0)
    {
        return res.dump();
    }
    else if (mysql_num_rows(dbRes) == 1)
    {
        res["isLoggedIn"] = true;
        return res.dump();
    }
    else
        return res.dump();
}

std::string requestHandler(char *r, MYSQL *con)
{
    json failedRequest = {
        {"success", false}};

    std::string request;
    request.append(r);
    json req = json::parse(request, nullptr, true);
    if (req.is_discarded())
    {
        return failedRequest.dump();
    }
    else
    {
        if (req["reqType"] == "register")
            return registerUser(req["email"], req["password"], req["passwordConfirm"], req["firstName"], req["lastName"], con);
        else if (req["reqType"] == "loginWithToken")
            return loginWithToken(req["email"], req["session_token"], con);
        else if (req["reqType"] == "login")
            return login(req["email"], req["password"], con);
        else
        {
            return failedRequest.dump();
        }
    }
}