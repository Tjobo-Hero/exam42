#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_client {
	int fd;
	int id;
	struct s_client *next;
} t_client;

int bufsize, clientCounter, sockfd;
fd_set allFD, readFD, writeFD;
struct sockaddr_in servaddr;

t_client *clients = NULL;

char message[1000000];

void	parseError(char *error) {
	write(STDERR_FILENO, error, strlen(error));
	exit(1);
}

void	initVar(int port) {
	bufsize = 1000000;
	clientCounter = 0;
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		parseError("Fatal error\n");
	FD_ZERO(&allFD);
	FD_SET(sockfd, &allFD);
}

int maxfd() {
	int ret = sockfd;
	t_client *tmp = clients;
	while (tmp) {
		if (tmp->fd > ret)
			ret = tmp->fd;
		tmp = tmp->next;
	}
	return ret;
}
void	cleanError() {
	t_client *tmp = clients;
	while(tmp) {
		t_client *del = tmp;
		tmp = tmp->next;
		close(del->fd);
		free(del);
	}
	close(sockfd);
	parseError("Fatal error\n");
}

void	sendMessage(char *message, int id)
{
	t_client *tmp = clients;
	while (tmp) {
		if (FD_ISSET(tmp->fd, &writeFD) && tmp->id != id)
		{
			printf("message:%s|\n", message);
			if (send(tmp->fd, message, strlen(message), 0) < 0)
				cleanError();
		}
		tmp = tmp->next;
	}
}

void	addNewClient(int newClientFD) {
	t_client *newClient = malloc(sizeof(t_client));
	if (!newClient)
		cleanError();
	newClient->fd = newClientFD;
	newClient->id = clientCounter;
	clientCounter++;
	newClient->next = NULL;
	FD_SET(newClient->fd, &allFD);
	if (!clients)
		clients = newClient;
	else
	{
		t_client *tmp = clients;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = newClient;
	}
	
}

void	createNewClient() {
	struct sockaddr_in cli;
	bzero(&cli, sizeof(cli));
	socklen_t len = sizeof(cli);
	int newClientFD = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (!newClientFD)
		cleanError();
	addNewClient(newClientFD);

	bzero(&message, sizeof(message));
	sprintf(message, "server: client %d just arrived\n", clientCounter - 1);
	sendMessage(message, -1);
}

void	deleteClient(t_client *client) {
	FD_CLR(client->fd, &allFD);
	close(client->fd);
	t_client *tmp = clients;
	if (tmp->id == client->id)
	{
		clients = tmp->next;
		free(client);
	}
	else
	{
		while (tmp)
		{
			if (tmp->next->fd == client->fd)
			{
				tmp->next = client->next;
				free(client);
				break;
			}
			tmp = tmp->next;
		}
	}
	bzero(&message, sizeof(message));

	sprintf(message, "server: client %d just left\n", client->id);
	sendMessage(message, -1);
}

void	createMessage(t_client *client) {
	char clientMessage[50];
	bzero(&clientMessage, sizeof(clientMessage));

	sprintf(clientMessage, "client %d: ", client->id);

	char ret[bufsize];
	bzero(&ret, sizeof(ret));

	char buf[bufsize];
	size_t i = 0;
	while (message[i]) {
		bzero(&buf, sizeof(buf));
		strcat(ret, clientMessage);
		size_t j = 0;
		while (message[i] && message[i] != '\n')
		{
			buf[j] = message[i];
			j++;
			i++;
		}
		if (message[i] == '\n')
		{
			buf[j] = message[i];
			i++;
		}
		strcat(ret, buf);
	}
	sendMessage(ret, client->id);
}

void	handleClient(t_client *client) {
	bzero(&message, sizeof(message));
	if (recv(client->fd, message, bufsize, 0) <= 0)
		deleteClient(client);
	else
	{
		createMessage(client);
	}
	
}

int main(int argc, char **argv) {
	if (argc != 2)
		parseError("Wrong number of arguments\n");
	initVar(atoi(argv[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		parseError("Fatal error\n");
	if (listen(sockfd, 250) != 0)
		parseError("Fatal error\n");
	int option = 1;
	setsockopt(sockfd, SOL_SOCKET,  SO_REUSEADDR, &option, 0);
	while (1) {
		writeFD = allFD;
		readFD = allFD;
		if (select(maxfd() + 1, &readFD, &writeFD, NULL, NULL) == -1)
			cleanError();
		if (FD_ISSET(sockfd, &readFD))
		{
			createNewClient();
			continue;
		}
		else
		{
			t_client *tmp = clients;
			while (tmp)
			{
				if (FD_ISSET(tmp->fd, &readFD))
				{
					handleClient(tmp);
					break;
				}
				tmp = tmp->next;
			}
		}
	}
	return 0;
}