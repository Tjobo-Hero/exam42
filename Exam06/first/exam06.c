#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_client
{
	int fd;
	int id;
	struct s_client *next;

} t_client;

t_client *clients = NULL;
int sockfd, bufsize, clientCounter;
struct sockaddr_in servaddr; // copied
fd_set readFD, writeFD, allFD;
char message[1000000];

void 	parseError(char *str) {
	write(STDERR_FILENO, str, strlen(str));
	exit(1);
}

void	setVariables(int listeningPort) {

	sockfd = 0;
	bufsize = 1000000;
	clientCounter = 0;
	bzero(&servaddr, sizeof(servaddr)); // copied
	servaddr.sin_family = AF_INET; // copied
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(listeningPort); // copied, except port
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // copied
		parseError("Fatal error\n");
	FD_ZERO(&allFD);
	FD_SET(sockfd, &allFD);
}


int		maxfd() {
	int ret = sockfd;
	t_client *tmp = clients;
	while(tmp) {
		if (tmp->fd > ret)
			ret = tmp->fd;
		tmp = tmp->next;
	}
	return ret;
}

void	cleanError() {
	t_client *tmp = clients;
	while (tmp) {
		t_client *del = tmp;
		tmp = tmp->next;
		free(del);
	}
	close(sockfd);
	parseError("Fatal error\n");
}

void	addClient(int newfd) {
	t_client *tmp = clients;
	t_client *newClient = malloc(sizeof(t_client));
	if (!newClient) {
		cleanError();
	}
	newClient->fd = newfd;
	newClient->id = clientCounter;
	clientCounter++;
	newClient->next = NULL;
	FD_SET(newClient->fd, &allFD);
	if (!clients)
		clients = newClient;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newClient;
	}
}

void 	sendMessage(const char *message, int id) {
	t_client *tmp = clients;
	while (tmp) {
		if (FD_ISSET(tmp->fd, &writeFD) && tmp->id != id)
			if (send(tmp->fd, message, strlen(message), 0) < 0)
				cleanError();
		tmp = tmp->next;
	}
}

void	createClient() {

	struct sockaddr_in cli;
	bzero(&cli, sizeof(cli));

	socklen_t len = sizeof(cli);
	int newfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (newfd < 0)
		cleanError();
	addClient(newfd);

	bzero(&message, sizeof(message));
	sprintf(message, "server: client %d just arrived\n", clientCounter - 1);

	sendMessage(message, -1);
}
void	deleteClient(t_client *client) {
	FD_CLR(client->fd, &allFD);
	close(client->fd);

	t_client *tmp = clients;
	if (tmp->id == client->id) {
		clients = tmp->next;
		free(client);
	}
	else {
		while (tmp) {
			if (tmp->next->fd == client->fd)
			{
				tmp->next = client->next;
				free(client);
				break;
			}
			tmp = tmp->next;
		}
	}
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

	int i = 0;
	while (message[i]) {
		bzero(&buf, sizeof(buf));
		strcat(ret, clientMessage);
		int j = 0;
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

void	client(t_client *client) {
	
	bzero(&message, sizeof(message));
	if (recv(client->fd, message, bufsize, 0) <= 0)
		deleteClient(client);
	else
		createMessage(client);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		parseError("Wrong number of arguments\n");
	setVariables(atoi(argv[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) // copied
		parseError("Fatal error\n");
	if (listen(sockfd, 250) != 0) // copied but changed 10 to 250
		parseError("Fatal error\n");

	while (1) {
		readFD = allFD;
		writeFD = allFD;
		if (select(maxfd() + 1, &readFD, &writeFD, NULL, NULL) == -1)
			cleanError();
		if (FD_ISSET(sockfd, &readFD)){
			createClient();
			continue;
		}
		else
		{
			t_client *tmp = clients;
			while (tmp){

				if (FD_ISSET(tmp->fd, &readFD))
				{
					client(tmp);
					break;
				}
				tmp = tmp->next;
			}
		}
	}

	return 0;
}