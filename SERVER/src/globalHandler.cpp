#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <string>
#include <openssl/sha.h>
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


// char *string = "testparola";
// 	char outputBUffer[65];
// 	sha256_string(string, outputBUffer);
// 	printf("%s", outputBUffer);
// 	if (strcmp(outputBUffer, "dddd81f800fdd7844147b35bfae4811f846c7dfbbb0f9b1102a341092540c17e") == 0)
// 		printf("WORKS");

std::string login(std::string email, std::string password)
{
    char hashedPassword[65];
    	sha256_string(password.c_str(), hashedPassword);
        
    return password+" "+hashedPassword;
}

std::string requestHandler(char *r)
{
    std::string request;
    request.append(r);
    json req = json::parse(request, nullptr, true);
    if (req.is_discarded())
    {
        std::string res = "rip";
        return res;
    }
    else if (req["reqType"] == "login")
        return login(req["email"], req["password"]);
    return "";
}