#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <string>
#include <openssl/sha.h>
#include "/usr/include/mysql/mysql.h"
using json = nlohmann::json;

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

std::string registerUser(std::string email, std::string password, std::string firstName, std::string lastName, MYSQL *con)
{
    char hashedPassword[65];
    sha256_string(password.c_str(), hashedPassword);
    char query[1024];
    int query_stat;
    sprintf(query, "insert into users(firstName,lastName, password) values('%s','%s','%s')", firstName.c_str(), lastName.c_str(), hashedPassword);

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
            {"generalError", "Error creating a new user. Try again later."},
            {"emailError", "Error email lol."},
            {"passwordError", "Password error"}};
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
            return registerUser(req["email"], req["password"], req["firstName"], req["lastName"], con);
    }
}
