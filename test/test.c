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
	char			msg[200000];
	struct s_client	*next;

}	t_client;

t_client	*clients = NULL;
int			sockfd; 
int			g_id = 0;
char		buf[200000];
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
t_client	*getClient(int fd)
{
	t_client *tmp = clients;

	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
	struct sockaddr_in	clientaddr;
	socklen_t			len = sizeof(clientaddr);

	new = malloc(sizeof(t_client));
	if (!new)
		printError();

	new->fd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);
	if (new->fd == -1)
	{
		free(new);
		printError();
	}

	new->id = g_id++;
	new->msg[0] = '\0';
	new->next = NULL;

	if (!clients)
		clients = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

	FD_SET(new->fd, &current);
	sprintf(buf, "server: client %d just arrived\n", new->id);
	sendToAll(new->fd);	
}

void	removeClient(int fd)
{
	t_client	*tmp = clients;
	t_client	*to_delete = NULL;

	sprintf(buf, "server: client %d just left\n", getClient(fd)->id);
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

		if (tmp && tmp->next)
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

void extract_message(t_client *client)
{
	char	tmp[200000];
	char	rest[200000];
	char	*newline;
	int		len;

	while ((newline = strstr(client->msg, "\n")))
	{
		len = newline - client->msg + 1;

		bzero(tmp, sizeof(tmp));
		bzero(rest, sizeof(rest));

		strcpy(tmp, client->msg);
		tmp[len] = '\0';

		strcpy(rest, client->msg + len);

		bzero(buf, sizeof(buf));
		sprintf(buf, "client %d: %s", client->id, tmp);
		sendToAll(client->fd);

		bzero(client->msg, sizeof(client->msg));
		strcpy(client->msg, rest);
	}
}

int main(int argc, char **argv)	{

	if (argc != 2)
	{
		printMessage("Wrong number of arguments\n");
		exit(1);
	}

	struct sockaddr_in servaddr; 
	bzero(&servaddr, sizeof(servaddr));
	t_client	*client;
	int			ret;
	int			fd;

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		printError();

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		printError();
	if (listen(sockfd, 100) != 0)
		printError();

	FD_ZERO(&current);
	FD_SET(sockfd, &current);

	while (1)
	{
		read_set = current;
		write_set = current;

		if (select(maxfd() + 1, &read_set, &write_set, NULL, NULL) == -1)
			continue;

		for (fd = 0; fd <= maxfd(); fd++)
		{
			if (!FD_ISSET(fd, &read_set))
				continue;

			if (fd == sockfd)
			{
				addClient();
				break;
			}
			
			client = getClient(fd);
			
			ret = recv(fd, client->msg + strlen(client->msg), sizeof(client->msg) - strlen(client->msg) - 1, 0);
		
			if (ret <= 0)
			{
				removeClient(fd);
				break;
			}
			
			client->msg[strlen(client->msg) + ret] = '\0';
			extract_message(client);
		}
	}
	return (0);
}
