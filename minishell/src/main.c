/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 19:34:06 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/28 12:11:32 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft.h"
#include "get_next_line.h"

#include "minishell.h"
#include "ms_error.h"
#include "ms_signals.h"
#include "ms_string.h"
#include "exec.h"

/* Event hook that forces readline to exit on ctrl-c */
static int	force_sigint_return(void)
{
	return (0);
}

static t_exit_code	get_stdin_fd(t_str file, int *fd)
{
	struct stat	statbuf;

	*fd = -1;
	if (file != NULL)
	{
		if (stat(file, &statbuf) == -1)
			return (ms_error(PERROR, file, NULL), E_CMD_NOT_FOUND);
		else if ((statbuf.st_mode & S_IFDIR) == S_IFDIR)
			return (ms_error(IS_DIR, file, NULL), E_CMD_NO_PERM);
		else if ((statbuf.st_mode & S_IRUSR) != S_IRUSR)
			return (ms_error(NO_PERM, file, NULL), E_CMD_NO_PERM);
		*fd = open(file, O_RDONLY);
	}
	else if (fstat(STDIN, &statbuf) == 0)
		*fd = dup(STDIN);
	if (*fd == -1)
		return (ms_error(PERROR, file, NULL), E_GEN_ERR);
	return (E_SUCCESS);
}

static t_exit_code	run_non_interative_mode(t_str file, t_alist *env_lst)
{
	int			fd;
	t_str		line;
	t_str		cmd;
	t_exit_code	exit_code;

	exit_code = get_stdin_fd(file, &fd);
	if (fd == -1)
		return (exit_code);
	line = get_next_line(fd);
	while (line != NULL && dup2(fd, STDIN) != -1
		&& g_signo != SIGINT && g_signo != SIGQUIT && ign_signal_handler())
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
	get_next_line(-1);
	return (free(line), exit_code);
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
	if (argc == 1)
		ft_putendl_fd("exit", STDOUT);
	return (exit_code);
}
