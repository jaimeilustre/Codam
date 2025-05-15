/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 14:10:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/15 14:47:13 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
