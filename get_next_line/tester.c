
// Mandatory part

// #include <stdio.h>
// #include <fcntl.h>
// #include "get_next_line.h"

// int main(void) {
//     int		fd;
//     char	*line;
// 	int		i;

//     fd = open("test1.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Error opening file");
//         return (1);
//     }
// 	i = 0;
//     while (i < 10 && (line = get_next_line(fd)) != NULL) {
//         printf("Line %d: %s", i + 1, line);
//         free(line);
// 		i++;
//     }
//     close(fd);
//     return (0);
// }
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 g    et_next_line.c get_next_line_utils.c tester.c

// Testing from standard input

#include <stdio.h>
#include "get_next_line.h"

int main(void) {
    int		fd;
    char	*line;
	int		i;

    fd = 0;
	i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line %d: %s", i + 1, line);
        free(line);
		i++;
    }
    return (0);
}

// Bonus part

// #include <stdio.h>
// #include <fcntl.h>
// #include "get_next_line_bonus.h"

// int main(void)
// {
// 	int fd1, fd2, fd3, i;
// 	char *line;

// 	// Open three files to obtain file descriptors.
// 	fd1 = open("test2.txt", O_RDONLY);
// 	fd2 = open("test3.txt", O_RDONLY);
// 	fd3 = open("test4.txt", O_RDONLY);

// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 	{
// 		perror("Error opening files");
// 		return (1);
// 	}
// 	line = get_next_line(42);
// 	if (!line)
// 		printf("fd 42: NULL\n");
// 	else
// 	{
// 		printf("fd 42: %s\n", line);
// 		free(line);
// 	}
// 	i = 0;
// 	while(i < 10)
// 	{
// 		// Read one line from each file descriptor.
// 		line = get_next_line(fd1);
// 		if (line)
// 		{
// 			printf("fd %d: %s", fd1, line);
// 			free(line);
// 		}

// 		line = get_next_line(fd2);
// 		if (line)
// 		{
// 			printf("fd %d: %s", fd2, line);
// 			free(line);
// 		}

// 		line = get_next_line(fd3);
// 		if (line)
// 		{
// 			printf("fd %d: %s", fd3, line);
// 			free(line);
// 		}
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line_bonus.c get_next_line_utils_bonus.c tester.c
