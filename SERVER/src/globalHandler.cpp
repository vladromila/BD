#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <string>
#include <openssl/sha.h>
#include "/usr/include/mysql/mysql.h"
#include <sys/stat.h>
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

std::string deleteUserCommand(std::string email, std::string commandId, MYSQL *con)
{
    json res = {
        {"success", false},
        {"runError", ""}};
    MYSQL_RES *dbRes;
    char initial_query[1024];
    int initial_query_stat;

    sprintf(initial_query, "SELECT id FROM users WHERE email='%s'", email.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    MYSQL_ROW userId = mysql_fetch_row(dbRes);
    std::string uID = std::string(userId[0]);

    bzero(initial_query, sizeof(initial_query));
    mysql_free_result(dbRes);

    sprintf(initial_query, "DELETE FROM commands WHERE id='%s'", commandId.c_str());

    mysql_query(con, initial_query);
    bzero(initial_query, sizeof(initial_query));
    mysql_free_result(dbRes);

    sprintf(initial_query, "SELECT id,name FROM commands WHERE user_id='%s' ORDER BY date DESC", uID.c_str());

    dbRes = mysql_store_result(con);

    MYSQL_ROW row;

    auto commands = json::array();

    while ((row = mysql_fetch_row(dbRes)))
    {
        json command;
        command["id"] = std::string(row[0]);
        command["name"] = std::string(row[1]);
        commands.push_back(command);
    }
    res["commands"] = commands;
    res["success"] = true;
    return res.dump();
}

std::string getUserCommands(std::string email, MYSQL *con)
{
    json res = {
        {"success", false},
        {"runError", ""}};
    MYSQL_RES *dbRes;
    char initial_query[1024];
    int initial_query_stat;

    sprintf(initial_query, "SELECT id FROM users WHERE email='%s'", email.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    MYSQL_ROW userId = mysql_fetch_row(dbRes);
    std::string uID = std::string(userId[0]);

    bzero(initial_query, sizeof(initial_query));
    mysql_free_result(dbRes);

    sprintf(initial_query, "SELECT id,name FROM commands WHERE user_id='%s' ORDER BY date DESC", uID.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    MYSQL_ROW row;

    auto commands = json::array();

    while ((row = mysql_fetch_row(dbRes)))
    {
        json command;
        command["id"] = std::string(row[0]);
        command["name"] = std::string(row[1]);
        commands.push_back(command);
    }
    res["commands"] = commands;
    res["success"] = true;
    return res.dump();
}

std::string getUserCommand(std::string id, MYSQL *con)
{
    json res = {
        {"success", false},
        {"runError", ""}};
    MYSQL_RES *dbRes;
    char initial_query[1024];
    int initial_query_stat;

    sprintf(initial_query, "SELECT data FROM commands WHERE id='%s'", id.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    MYSQL_ROW commD = mysql_fetch_row(dbRes);
    std::string commData = std::string(commD[0]);

    bzero(initial_query, sizeof(initial_query));
    mysql_free_result(dbRes);
    res["command"] = commData;
    res["success"] = true;
    return res.dump();
}

std::string runCommand(std::string email, std::string execDate, std::string trc, MYSQL *con)
{
    json res = {
        {"success", false},
        {"runError", ""}};
    MYSQL_RES *dbRes;
    char initial_query[1024];
    int initial_query_stat;

    sprintf(initial_query, "SELECT id FROM users WHERE email='%s'", email.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    MYSQL_ROW userId = mysql_fetch_row(dbRes);
    std::string uID = std::string(userId[0]);
    bool rootFolderExists = false;
    bool userFolderExists = false;
    bool commandExecutionExists = false;
    char homeDir[256];
    strcpy(homeDir, "/var/www");
    strcat(homeDir, "/DDP");
    struct stat st;
    if (stat(homeDir, &st) == 0)
    {
        if (!(st.st_mode & S_IFDIR != 0))
        {
            rootFolderExists = false;
        }
        else
            rootFolderExists = true;
    }
    else
    {
        rootFolderExists = false;
    }

    if (rootFolderExists)
        printf("Root folder exists.\n");
    else
    {
        const int dir_err = mkdir(homeDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            printf("Error creating root folder.\n");
        }
        else
            printf("Root folder created.\n");
    }
    strcat(homeDir, "/");
    strcat(homeDir, uID.c_str());
    if (stat(homeDir, &st) == 0)
    {
        if (!(st.st_mode & S_IFDIR != 0))
        {
            userFolderExists = false;
        }
        else
            userFolderExists = true;
    }
    else
    {
        userFolderExists = false;
    }

    if (userFolderExists)
        printf("User folder exists.\n");
    else
    {
        const int dir_err = mkdir(homeDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            printf("Error creating user folder.\n");
        }
        else
            printf("User folder created.\n");
    }

    strcat(homeDir, "/");
    strcat(homeDir, execDate.c_str());
    const int dir_err = mkdir(homeDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (-1 == dir_err)
    {
        printf("Error creating execution folder.\n");
    }
    else
        printf("Execution folder created.\n");
    char outputPath[512];
    char errorPath[512];
    char resultPath[512];

    strcpy(outputPath, homeDir);
    strcpy(errorPath, homeDir);
    strcpy(resultPath, homeDir);
    strcat(outputPath, "/output.txt");
    strcat(errorPath, "/error.txt");
    strcat(resultPath, "/result.txt");

    strcat(homeDir, "/command.sh");

    std::fstream executionFile;
    executionFile.open(homeDir, std::ios::out);
    executionFile << trc.c_str();
    executionFile.close();

    std::string toRunCommand;
    // toRunCommand+="chmod 777 ";
    // toRunCommand+=std::string(homeDir);
    toRunCommand += "sh ";
    toRunCommand += std::string(homeDir);
    toRunCommand += " >";
    toRunCommand += std::string(outputPath);
    toRunCommand += " 2>";
    toRunCommand += std::string(errorPath);
    printf("%s\n", toRunCommand.c_str());
    system(toRunCommand.c_str());

    std::string finalRes;
    std::string row;

    std::fstream outputFile;
    outputFile.open(outputPath, std::ios::in);

    while (getline(outputFile, row))
    {
        finalRes += row;
        finalRes += '\n';
    }
    outputFile.close();

    std::fstream errorFile;

    errorFile.open(errorPath, std::ios::in);

    while (getline(errorFile, row))
    {
        finalRes += row;
        finalRes += '\n';
    }
    errorFile.close();

    std::fstream resultFile;
    resultFile.open(resultPath, std::ios::out);
    resultFile << finalRes;

    resultFile.close();
    res["response"] = finalRes;
    res["commandForWebPreview"] = "xdg-open http://167.172.38.89/executions/" + uID + "/" + execDate + "/result.txt";
    std::string fres = std::to_string(res.dump().length() + 1);
    fres += '~';
    fres += res.dump();
    return fres;
}

std::string saveNewCommand(std::string email, std::string commandName, std::string commandData, MYSQL *con)
{
    json res = {
        {"success", false},
        {"saveError", ""}};
    MYSQL_RES *dbRes;
    char initial_query[1024];
    int initial_query_stat;
    sprintf(initial_query, "SELECT id FROM commands WHERE name='%s'", commandName.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    if (mysql_num_rows(dbRes))
    {
        res["saveError"] = "A command with this name already exists";
        return res.dump();
    }

    mysql_free_result(dbRes);
    bzero(initial_query, sizeof(initial_query));

    sprintf(initial_query, "SELECT id FROM users WHERE email='%s'", email.c_str());

    mysql_query(con, initial_query);
    dbRes = mysql_store_result(con);

    MYSQL_ROW userId = mysql_fetch_row(dbRes);
    std::string uID = std::string(userId[0]);

    printf("%s\n", uID.c_str());

    char query[1024 + commandData.length()];
    int query_stat;
    sprintf(query, "insert into commands(user_id,name,data, date) values(%s,'%s','%s',CURDATE())", uID.c_str(), commandName.c_str(), commandData.c_str());

    // printf("%s\n", query);

    query_stat = mysql_query(con, query);
    if (query_stat != 0)
    {
        res["saveError"] = "Error saving the command.";
        return res.dump();
    }
    else
    {
        mysql_free_result(dbRes);
        bzero(initial_query, sizeof(initial_query));
        sprintf(initial_query, "SELECT id FROM commands WHERE user_id='%s' ORDER BY id DESC", uID.c_str());
        printf("%s\n\n", initial_query);
        mysql_query(con, initial_query);
        dbRes = mysql_store_result(con);

        MYSQL_ROW currentIdString = mysql_fetch_row(dbRes);
        std::string currentId = std::string(currentIdString[0]);

        res["commandId"] = currentId;

        res["success"] = true;
        return res.dump();
    }
}

std::string saveCommand(std::string commandId, std::string commandData, MYSQL *con)
{
    json res = {
        {"success", false},
        {"saveError", ""}};

    char query[1024 + commandData.length()];
    int query_stat;
    sprintf(query, "UPDATE commands SET data='%s',date=CURDATE() WHERE id=%s", commandData.c_str(), commandId.c_str());

    query_stat = mysql_query(con, query);
    if (query_stat != 0)
    {
        res["saveError"] = "Error updating the command.";
        return res.dump();
    }
    else
    {
        res["success"] = true;
        return res.dump();
    }
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

std::string updateUser(std::string oldEmail, std::string email, std::string password, std::string passwordConfirm, std::string firstName, std::string lastName, MYSQL *con)
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
    bool updatePassword = true;
    if (password.size() > 0)
    {
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
    }
    else
    {
        updatePassword = false;
    }
    if (isAnyError == true)
    {
        return res.dump();
    }

    char hashedPassword[65];
    sha256_string(password.c_str(), hashedPassword);
    char query[1024];
    int query_stat;
    if (updatePassword == true)
        sprintf(query, "UPDATE users SET email='%s', firstName='%s', lastName='%s', password='%s' WHERE email='%s'", email.c_str(), firstName.c_str(), lastName.c_str(), hashedPassword, oldEmail.c_str());
    else
        sprintf(query, "UPDATE users SET email='%s', firstName='%s', lastName='%s' WHERE email='%s'", email.c_str(), firstName.c_str(), lastName.c_str(), oldEmail.c_str());

    query_stat = mysql_query(con, query);
    if (query_stat != 0)
    {
        res["passwordConfirm"] = "Error updating user. Try again later.";
        return res.dump();
    }
    else
    {
        res["success"] = true;
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
        if (req["reqType"] == "deleteUserCommand")
            return deleteUserCommand(req["email"], req["id"], con);
        else if (req["reqType"] == "getUserCommand")
            return getUserCommand(req["id"], con);
        else if (req["reqType"] == "getUserCommands")
            return getUserCommands(req["email"], con);
        else if (req["reqType"] == "updateUser")
            return updateUser(req["oldEmail"], req["email"], req["password"], req["passwordConfirm"], req["firstName"], req["lastName"], con);
        else if (req["reqType"] == "register")
            return registerUser(req["email"], req["password"], req["passwordConfirm"], req["firstName"], req["lastName"], con);
        else if (req["reqType"] == "loginWithToken")
            return loginWithToken(req["email"], req["session_token"], con);
        else if (req["reqType"] == "login")
            return login(req["email"], req["password"], con);
        else if (req["reqType"] == "saveNewCommand")
            return saveNewCommand(req["email"], req["commandName"], req["commandData"], con);
        else if (req["reqType"] == "saveCommand")
            return saveCommand(req["commandId"], req["commandData"], con);
        else if (req["reqType"] == "runCommand")
            return runCommand(req["email"], req["execDate"], req["toRunCommand"], con);
        else
        {
            return failedRequest.dump();
        }
    }
}