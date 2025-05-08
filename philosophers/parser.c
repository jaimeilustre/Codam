/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:54:12 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/08 17:17:47 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "philo.h"

/*Initialize arguments from argv*/
bool	initialize_args(char *arg, int index, t_data *data)
{
	long	nb_long;

	if (!valid_int(arg))
		return (false);
	nb_long = ft_strtol(arg);
	if (nb_long > INT_MAX || nb_long <= 0)
		return (false);
	if (index == 0)
		data->nb_of_philos = (int)nb_long;
	else if (index == 1)
		data->time_to_die = (int)nb_long;
	else if (index == 2)
		data->time_to_eat = (int)nb_long;
	else if (index == 3)
		data->time_to_sleep = (int)nb_long;
	else if (index == 4)
		data->nb_of_meals_per_philo = (int)nb_long;
	return (true);
}

/*Parse arguments into struct*/
bool	parse_args(int argc, char **argv, t_data *data)
{
	int		i;

	ft_memset(data, 0, sizeof(t_data));
	i = 0;
	while (i < argc - 1)
	{
		if (!initialize_args(argv[i + 1], i, data))
			return (false);
		i++;
	}
	if (argc == 5)
		data->nb_of_meals_per_philo = -1;
	return (true);
}

/*Initialize mutexes*/
bool	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

/*Initialize data in struct*/
bool	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!data->forks)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->philos)
		return (free(data->forks), false);
	if (pthread_mutex_init(&data->print, NULL))
		return (free(data->forks), free(data->philos), false);
	return (true);
}

/*Initialize philo struct*/
void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time_since_last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_of_philos];
		i++;
	}
}
