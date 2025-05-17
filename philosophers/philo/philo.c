/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 08:08:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/17 13:09:04 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "philo.h"

/*Frees the forks array and destroys the mutexes*/
void	free_and_destroy(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (data->forks_init && data->forks_init[i])
				pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->forks_init)
		free(data->forks_init);
	if (data->philos)
		free(data->philos);
	if (data->meal_mutex_init)
		pthread_mutex_destroy(&data->meal_mutex);
	if (data->print_mutex_init)
		pthread_mutex_destroy(&data->print_mutex);
	if (data->death_mutex_init)
		pthread_mutex_destroy(&data->death_mutex);
}

/*Checks if any deaths occured during the simulation*/
static bool	death_check(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&data->death_mutex);
	status = data->deaths;
	pthread_mutex_unlock(&data->death_mutex);
	return (status);
}

/*Philosopher's routine*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(10);
	while (1)
	{
		if (death_check(philo->data))
			break ;
		think(philo);
		take_forks(philo);
		eat(philo);
		return_forks(philo);
		if (death_check(philo->data))
			break ;
		sleeping(philo);
		if (philo->data->max_meals > 0
			&& philo->meals_eaten >= philo->data->max_meals)
			break ;
	}
	return (NULL);
}

/*Main program logic*/
int	philo(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	int			i;

	if (!parse_and_init(argc, argv, &data))
		return (EXIT_FAILURE);
	data.start_time = get_current_time();
	if (!create_philo_thread(&data))
		exit_error(&data, "Error with creating philo thread");
	if (pthread_create(&monitor_thread, NULL, monitor, &data) != 0)
		exit_error(&data, "Error with creating monitor thread");
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.nb_of_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	free_and_destroy(&data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc >= 5 && argc <= 6)
		philo(argc, argv);
	else if (argc <= 4)
		ft_putendl_fd("Too few arguments", 2);
	else
		ft_putendl_fd("Too many arguments", 2);
	return (0);
}
