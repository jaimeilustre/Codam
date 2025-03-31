/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 19:34:06 by jboon         #+#    #+#                 */
/*   Updated: 2025/03/20 17:00:10 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include "signal_utils.h"
#include "ms_error.h"
#include "exec.h"

static void	setup_signals(t_sigaction *sig)
{
	if (!init_sig(sig, 0, interative_mode, NULL))
	{
		ms_error(PERROR, NULL, NULL);
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

static void	run_non_interative_mode(t_str file, t_alist *env_lst)
{
	int		fd;
	t_str	line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ms_error(PERROR, file, NULL));
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_newline_at_end(line);
		if (!is_empty_cmd(line))
			exec_prompt(line, env_lst);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	run_interactive_mode(t_alist *env_lst)
{
	t_str		cmd;

	cmd = "";
	while (cmd != NULL)
	{
		cmd = cmd_prompt("$");
		if (cmd != NULL && *cmd != '\0')
			exec_prompt(cmd, env_lst);
		free(cmd);
	}
}

int	main(int argc, t_str argv[], t_str *env)
{
	t_sigaction	sig;
	t_alist		env_lst;

	if (init_env(&env_lst, env) == false)
		return (ms_error(PERROR, "env_lst", NULL), EXIT_FAILURE);
	if (argc > 1)
		run_non_interative_mode(argv[1], &env_lst);
	else
	{
		setup_signals(&sig);
		run_interactive_mode(&env_lst);
	}
	rl_clear_history();
	free_list(&env_lst);
	return (EXIT_SUCCESS);
}
