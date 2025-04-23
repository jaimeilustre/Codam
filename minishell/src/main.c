/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 19:34:06 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/22 11:20:27 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include "ms_signals.h"
#include "ms_error.h"
#include "exec.h"

/* Event hook that forces readline to exit on ctrl-c */
static int	force_sigint_return(void)
{
	return (0);
}

static int	get_stdin_fd(t_str file)
{
	struct stat	statbuf;

	if (file != NULL)
		return (open(file, O_RDONLY));
	else if (fstat(STDIN, &statbuf) == 0)
		return (dup(STDIN));
	return (-1);
}

static t_exit_code	run_non_interative_mode(t_str file, t_alist *env_lst)
{
	int			fd;
	t_str		line;
	t_str		cmd;
	t_exit_code	exit_code;

	fd = get_stdin_fd(file);
	if (fd == -1)
		return (ms_error(PERROR, file, NULL), E_CMD_NOT_FOUND);
	exit_code = E_SUCCESS;
	line = get_next_line(fd);
	while (line != NULL && dup2(fd, STDIN) != -1)
	{
		cmd = ft_strtrim(line, "\n");
		if (!is_empty_cmd(cmd))
		{
			exit_code = exec_prompt(cmd, env_lst);
			store_exit_code(env_lst, exit_code);
		}
		free(cmd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (exit_code);
}

static t_exit_code	run_interactive_mode(t_alist *env_lst)
{
	t_str		cmd;
	t_exit_code	exit_code;

	exit_code = E_SUCCESS;
	rl_event_hook = force_sigint_return;
	while (1)
	{
		g_signo = 0;
		if (!trap_prompt_signals())
			return (ms_error(PERROR, NULL, NULL), E_GEN_ERR);
		cmd = cmd_prompt("$");
		if (cmd == NULL)
			break ;
		else if (g_signo == SIGINT)
			store_exit_code(env_lst, E_TERM);
		else if (*cmd != '\0')
		{
			exit_code = exec_prompt(cmd, env_lst);
			store_exit_code(env_lst, exit_code);
		}
		free(cmd);
	}
	return (exit_code);
}

int	main(int argc, t_str argv[], t_str *env)
{
	t_alist		env_lst;
	t_exit_code	exit_code;

	if (init_env(&env_lst, env) == false)
		return (ms_error(PERROR, "env_lst", NULL), E_GEN_ERR);
	if (argc > 1)
		exit_code = run_non_interative_mode(argv[1], &env_lst);
	else if (!isatty(STDIN))
		exit_code = run_non_interative_mode(NULL, &env_lst);
	else
		exit_code = run_interactive_mode(&env_lst);
	rl_clear_history();
	free_list(&env_lst);
	ft_putendl_fd("exit", STDOUT);
	return (exit_code);
}
