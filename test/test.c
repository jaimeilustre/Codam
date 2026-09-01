#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

typedef struct s_client
{
	int				fd;
	int				id;
	struct s_client	*next;

}	t_client;

t_client	*clients = NULL;
int			sockfd, g_id;
char		msg[200000];
char		buf[200000];
fd_set		current, read_set, write_set;

// Prints message to standard error
void	printMessage(char *message)
{
	write(2, msg, strlen(msg));
}

// Prints fatal error message and exits
void	printError()
{
	printMessage("Fatal error\n");
	close(sockfd);
	exit(1);
}

// Returns the highest fd for select's first argument
int maxfd()
{
	int			max = sockfd;
	t_client	*tmp = clients;

	while (tmp)
	{
		if (tmp->fd > max)
			max = tmp->fd;
		tmp = tmp->next;
	}
	return (max);
}

// Returns the client's id
int	getid(int fd)
{
	t_client *tmp = clients;

	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp->id);
		tmp = tmp->next;
	}
	return (-10);
}

// Sends the global buf string
void	sendToAll(int fd)
{
	t_client	*tmp = clients;

	while (tmp)
	{
		if (tmp->fd != fd && FD_ISSET(tmp->fd, &write_set))
		{
			if (send(tmp->fd, buf, strlen(buf), 0) == -1)
				printError();
		}
		tmp = tmp->next;
	}
}

void	addClient()
{
	t_client			*tmp = clients;
	t_client			*new;
	int					client;
	struct sockaddr_in	clientaddr;
	socklen_t			len = sizeof(clientaddr);

	client = accept(sockfd, (struct sockaddr *)&clientaddr, &len);
	if (client == -1)
		printError();

	bzero(&buf, sizeof(buf));
	sprintf("server: client %d just arrived\n", g_id);
	sendToAll(client);
	FD_SET(client, &current);
	new = malloc(sizeof(t_client));
	if (!new)
		printError();
	new->fd = client;
	new->id = g_id++;
	new->next = NULL;
	if (!clients)
		clients = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	removeClient(int fd)
{

}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)	{

	if (argc != 2)
	{
		printMessage("Wrong number of arguments\n");
		exit(1);
	}

	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printError();
	} 

	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(8081); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		printError();
	}

	if (listen(sockfd, 100) != 0) {
		printError();
	}
	len = sizeof(cli);
	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n");
}