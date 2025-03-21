/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 16:55:25 by jboon         #+#    #+#                 */
/*   Updated: 2025/02/14 17:41:53 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

static bool	parse_flag(t_str arg)
{
	if (*arg != '-' || (*arg == '-' && *(arg + 1) == '\0'))
		return (false);
	while (*(++arg) != '\0')
	{
		if (*arg != 'n')
			return (false);
	}
	return (true);
}

static t_str	*check_argv_flags(t_str *argv, bool *append_newline)
{
	while (*argv)
	{
		if (parse_flag(*argv))
			*append_newline = false;
		else
			return (argv);
		++argv;
	}
	return (argv);
}

static void	print_arguments(t_str *argv)
{
	bool	append_newline;

	append_newline = true;
	argv = check_argv_flags(argv, &append_newline);
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		++argv;
		if (*argv != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (append_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	echo(int argc, t_str *argv, t_alist *env_lst)
{
	(void)env_lst;
	if (argc > 1)
		print_arguments(argv + 1);
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
