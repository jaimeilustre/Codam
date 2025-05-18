/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:54:12 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/18 07:56:26 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "philo.h"

/*Initialize arguments from argv*/
static bool	initialize_args(char *arg, int index, t_data *data)
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
		data->max_meals = (int)nb_long;
	return (true);
}

/*Parse arguments into struct*/
static bool	parse_args(int argc, char **argv, t_data *data)
{
	int		i;

	memset(data, 0, sizeof(t_data));
	i = 0;
	while (i < argc - 1)
	{
		if (!initialize_args(argv[i + 1], i, data))
			return (false);
		i++;
	}
	if (argc == 5)
		data->max_meals = -1;
	return (true);
}

/*Initialize data in struct*/
static bool	init_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!data->forks)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->philos)
		return (free(data->forks), false);
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
	return (true);
}

/*Initialize mutexes*/
static bool	init_mutex(t_data *data)
{
	int	i;

	data->forks_init = malloc(sizeof(bool) * data->nb_of_philos);
	if (!data->forks_init)
		return (false);
	memset(data->forks_init, 0, sizeof(bool) * data->nb_of_philos);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		data->forks_init[i] = true;
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (free(data->forks), free(data->philos), false);
	data->print_mutex_init = true;
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (free(data->forks), free(data->philos), false);
	data->meal_mutex_init = true;
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (free(data->forks), free(data->philos), false);
	data->death_mutex_init = true;
	return (true);
}

/*Putting it all together*/
bool	parse_and_init(int argc, char **argv, t_data *data)
{
	if (!parse_args(argc, argv, data))
	{
		if (exit_error(data, "Error with parsing") != 0)
			return (false);
	}
	if (!init_data(data))
	{
		if (exit_error(data, "Error with initialising struct data") != 0)
			return (false);
	}
	if (!init_mutex(data))
	{
		if (exit_error(data, "Error with mutex") != 0)
			return (false);
	}
	return (true);
}
