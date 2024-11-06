
// Mandatory part

// #include <stdio.h>
// #include <fcntl.h>

// #include "get_next_line.h"

// int main(int argc, char **argv) {
//     int		fd;
//     char	*line;
// 	int		i;

//     if (argc != 2) {
//         printf("Usage: %s <file_name>\n", argv[0]);
//         return (1);
//     }
//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1) {
//         perror("Error opening file");
//         return (1);
//     }
// 	i = 0;
// 	// // while loop to print all lines with only 1 file descriptor
//     // while ((line = get_next_line(fd)) != NULL) {
//     //     printf("Line %d: %s", i + 1, line);
//     //     free(line);
// 	// 	i++;
//     // }
// 	// print one line at a time 
// 	line = get_next_line(fd);
// 	i++;
// 	if (line != NULL)
// 	{
// 		printf("Line %d: %s", i, line);
//         free(line);
// 		i++;
// 	}
// 	line = get_next_line(fd);
// 	if (line != NULL)
// 	{
// 		printf("Line %d: %s", i, line);
//         free(line);
// 		i++;
// 	}
// 	line = get_next_line(fd);
// 	if (line != NULL)
// 	{
// 		printf("Line %d: %s", i, line);
//         free(line);
// 		i++;
// 	}
// 	line = get_next_line(fd);
// 	if (line != NULL)
// 	{
// 		printf("Line %d: %s", i, line);
//         free(line);
// 		i++;
// 	}
// 	line = get_next_line(fd);
// 	if (line != NULL)
// {
// 		printf("Line %d: %s", i, line);
//         free(line);
// 		i++;
// 	}
//     close(fd);
//     return (0);
// }
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c tester.c

// Bonus part

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main(void)
{
	int fd1, fd2, fd3;
	char *line;

	// Open three files to obtain file descriptors.
	fd1 = open("test2.txt", O_RDONLY);
	fd2 = open("test3.txt", O_RDONLY);
	fd3 = open("test4.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		perror("Error opening files");
		return (1);
	}
	line = get_next_line(42);
	if (line == NULL)
		printf("fd 42: NULL\n");
	else
	{
		printf("fd 42: %s\n", line);
		free(line);
	}

	// Read from each file descriptor in a round-robin manner.
	for (int i = 0; i < 10; i++)  // Adjust loop count as needed.
	{
		// Read one line from each file descriptor.
		line = get_next_line(fd1);
		if (line)
		{
			printf("fd %d: %s", fd1, line);
			free(line);
		}

		line = get_next_line(fd2);
		if (line)
		{
			printf("fd %d: %s", fd2, line);
			free(line);
		}

		line = get_next_line(fd3);
		if (line)
		{
			printf("fd %d: %s", fd3, line);
			free(line);
		}
	}
	// Close the file descriptors.
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}


