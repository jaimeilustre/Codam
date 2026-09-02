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
char		msg[200000], buf[200000];
fd_set		current, read_set, write_set;

// Prints message to standard error
void	printMessage(char *msg)
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
int	getId(int fd)
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
	sprintf(buf, "server: client %d just arrived\n", g_id);
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
	t_client	*tmp = clients;
	t_client	*to_delete = NULL;

	bzero(&buf, sizeof(buf));
	sprintf(buf, "server: client %d just left\n", getId(fd));
	sendToAll(fd);
	if (clients && clients->fd == fd)
	{
		to_delete = clients;
		clients = clients->next;
	}
	else
	{
		while (tmp && tmp->next && tmp->next->fd != fd)
			tmp = tmp->next;
		if (tmp && tmp->next && tmp->next->fd == fd)
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
		}
	}
	if (to_delete)
		free(to_delete);
	FD_CLR(fd, &current);
	close (fd);
}

void extract_message(int fd)
{
	char	tmp[200000];
	int		i = -1;
	int		j = -1;

	bzero(&tmp, sizeof(tmp));
	while (msg[++i] != 0)
	{
		tmp[++j] = msg[i];
		if (msg[i] == '\n')
		{
			bzero(&buf, sizeof(buf));
			sprintf(buf, "client %d: %s", getId(fd), tmp);
			sendToAll(fd);
			bzero(&tmp, sizeof(tmp));
			j = -1;
		}
	}
	bzero(&msg, sizeof(msg));
}

int main(int argc, char **argv)	{

	if (argc != 2)
	{
		printMessage("Wrong number of arguments\n");
		exit(1);
	}

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printError();
	}

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		printError();
	}
	if (listen(sockfd, 100) != 0) {
		printError();
	}

	FD_ZERO(&current);
	FD_SET(sockfd, &current);
	bzero(&msg, sizeof(msg));

	while (1)
	{
		read_set = write_set = current;
		if (select(maxfd() + 1, &read_set, &write_set, NULL, NULL) == -1)
			continue;
		for (int fd = 0; fd <= maxfd(); ++fd)
		{
			if (FD_ISSET(fd, &read_set))
			{
				if (fd == sockfd)
				{
					addClient();
					break;
				}
				int ret = 1;
				while (ret == 1 && msg[strlen(msg) - 1] != '\n')
				{
					ret = recv(fd, msg + strlen(msg), 1, 0);
					if (ret <= 0)
						break;
				}

				if (ret <= 0)
				{
					removeClient(fd);
					break;
				}
				extract_message(fd);
			}
		}
	}
	return (0);
}
