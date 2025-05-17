/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 14:10:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/17 17:35:09 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "philo.h"

/*Creates philo processes*/
bool	create_philo_processes(t_data *data)
{
	int		i;
	pid_t	pid;

	data->start_time = get_current_time();
	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].time_since_last_meal = get_current_time();
		pid = fork();
		if (pid < 0)
			return (false);
		else if (pid == 0)
		{
			routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		else
			data->philos[i].pid = pid;
		i++;
	}
	return (true);
}

/*Handle exit process*/
void	wait_and_handle_exit(t_data *data)
{
	int		status;
	pid_t	pid;
	int		i;

	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		i = 0;
		while (i < data->nb_of_philos)
			kill(data->philos[i++].pid, SIGKILL);
	}
	i = 1;
	while (i < data->nb_of_philos)
		waitpid(data->philos[i++].pid, NULL, 0);
}
