/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 19:34:06 by jboon         #+#    #+#                 */
/*   Updated: 2025/01/27 18:56:47 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include "signal_utils.h"
#include "ms_error.h"

extern char	**environ;

static void	setup_signals(t_sigaction *sig)
{
	if (!init_sig(sig, 0, interative_mode, NULL))
	{
		ms_error(PERROR, NULL);
		exit(EXIT_FAILURE);
	}
}

static void	remove_newline_at_end(t_str line)
{
	size_t	len;

	len = ft_strlen(line);
	if (*(line + len - 1) == '\n')
		*(line + len - 1) = '\0';
}

static void	run_non_interative_mode(t_str file)
{
	int		fd;
	t_str	line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ms_error(PERROR, file));
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_newline_at_end(line);
		if (!is_empty_cmd(line))
			exe_cmd(line, environ);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	run_interactive_mode(void)
{
	t_str		cmd;

	cmd = "";
	while (cmd != NULL)
	{
		cmd = cmd_prompt("$");
		if (cmd != NULL && *cmd != '\0')
			exe_cmd(cmd, environ);
		free(cmd);
	}
}

int	main(int argc, char *argv[])
{
	t_sigaction	sig;

	if (argc > 1)
		run_non_interative_mode(argv[1]);
	else
	{
		setup_signals(&sig);
		run_interactive_mode();
	}
	return (EXIT_SUCCESS);
}
