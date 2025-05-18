/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 14:10:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/18 07:44:07 by jaimeilustr   ########   odam.nl         */
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
	int		philos_done_eating;

	philos_done_eating = 0;
	while (philos_done_eating < data->nb_of_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			i = 0;
			while (i < data->nb_of_philos)
				kill(data->philos[i++].pid, SIGKILL);
			break ;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
			philos_done_eating++;
	}
}
