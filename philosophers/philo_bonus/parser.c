/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:54:12 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/18 07:53:09 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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

/*Initialize data in structs*/
static bool	init_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->philos)
		return (false);
	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time_since_last_meal = 0;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

/*Initialize semaphores*/
static bool	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meal");
	sem_unlink("/death");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_of_philos);
	if (data->forks == SEM_FAILED)
		return (false);
	data->forks_sem_init = true;
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (false);
	data->print_sem_init = true;
	data->meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
		return (false);
	data->meal_sem_init = true;
	data->death_sem = sem_open("/death", O_CREAT, 0644, 1);
	if (data->death_sem == SEM_FAILED)
		return (false);
	data->death_sem_init = true;
	return (true);
}

/*Putting it all together*/
void	parse_and_init(int argc, char **argv, t_data *data)
{
	if (!parse_args(argc, argv, data))
		exit_error(data, "Error with parsing");
	if (!init_data(data))
		exit_error(data, "Error with initialising");
	if (!init_semaphores(data))
		exit_error(data, "Error with semaphores");
}
