/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 14:10:54 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/14 15:51:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Creates philo threads*/
bool	create_philo_processes(t_data *data)
{
	int		i;
	pid_t	pid;

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

/*Checks if everyone ate their max meals already*/
static bool	max_meals_reached(t_data *data)
{
	int		i;
	bool	result;

	result = true;
	if (data->max_meals <= 0)
		return (false);
	sem_wait(data->meal_sem);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			result = false;
			break ;
		}
		i++;
	}
	sem_post(data->meal_sem);
	return (result);
}

/*Checks for philosopher death and updates flag and message*/
static bool	check_philosopher_death(t_data *data)
{
	int		i;
	size_t	meal_time;

	i = 0;
	while (i < data->nb_of_philos)
	{
		sem_wait(data->meal_sem);
		meal_time = get_current_time()
			- data->philos[i].time_since_last_meal;
		sem_post(data->meal_sem);
		if (meal_time > (size_t)data->time_to_die)
		{
			sem_wait(data->death_sem);
			data->deaths = 1;
			sem_post(data->death_sem);
			sem_wait(data->print_sem);
			printf("%lu %d died\n", get_current_time() - data->start_time,
				data->philos[i].id);
			sem_post(data->print_sem);
			return (true);
		}
		i++;
	}
	return (false);
}

/*Monitor process*/
void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_philosopher_death(data))
			return (NULL);
		if (max_meals_reached(data))
		{
			sem_wait(data->death_sem);
			data->deaths = 1;
			sem_post(data->death_sem);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}
