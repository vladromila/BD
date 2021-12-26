#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./src/globalHandler.cpp"
#include "/usr/include/mysql/mysql.h"
#define PORT 3000

struct connection_details
{
	const char *server, *user, *password, *database;
};

MYSQL *mysql_connection_setup(struct connection_details mysql_details)
{
	MYSQL *connection = mysql_init(NULL);

	if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0))
	{
		std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
		exit(1);
	}

	return connection;
}

int main()
{
	MYSQL *con;		// the connection
	MYSQL_RES *res; // the results
	MYSQL_ROW row;	// the results rows (array)

	struct connection_details mysqlD;
	mysqlD.server = "localhost"; // where the mysql database is
	mysqlD.user = "vlad";		 // user
	mysqlD.password = "bd2021";	 // the password for the database
	mysqlD.database = "DDP";	 // the databse

	con = mysql_connection_setup(mysqlD);
	printf("[+]Server connected to the database.\n");

	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", PORT);

	if (listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}
	else
	{
		printf("[-]Error in binding.\n");
	}

	while (1)
	{
		newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
		if (newSocket < 0)
		{
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if ((childpid = fork()) == 0)
		{
			close(sockfd);

			while (1)
			{
				recv(newSocket, buffer, 1024, 0);
				if (strcmp(buffer, ":exit") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}
				else
				{
					printf("Client: %s\n", buffer);
					std::string res = requestHandler(buffer, con);
					send(newSocket, res.c_str(), res.size() + 1, 0);
					bzero(buffer, sizeof(buffer));
				}
			}
		}
	}

	close(newSocket);

	mysql_free_result(res);

	mysql_close(con);

	return 0;
}