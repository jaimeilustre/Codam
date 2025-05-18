/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 08:08:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/18 07:48:09 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "philo.h"

/*Monitor thread within each philo process that checks for deaths*/
void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	size_t	time_since;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->meal_sem);
		time_since = get_current_time() - philo->time_since_last_meal;
		sem_post(philo->data->meal_sem);
		if (time_since > (size_t)philo->data->time_to_die)
		{
			if (sem_wait(philo->data->death_sem) == 0)
			{
				sem_wait(philo->data->print_sem);
				printf("%lu %d died\n", get_current_time()
					- philo->data->start_time, philo->id);
				sem_post(philo->data->print_sem);
				exit(EXIT_FAILURE);
			}
		}
		ft_usleep(1);
	}
	return (NULL);
}

/*Philosopher's routine*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (pthread_create(&philo->monitor_thread, NULL,
			monitor_routine, philo) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(philo->monitor_thread);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		return_forks(philo);
		sleeping(philo);
		if (philo->data->max_meals > 0
			&& philo->meals_eaten >= philo->data->max_meals)
			exit(EXIT_SUCCESS);
	}
	return (NULL);
}

/*Main program logic*/
int	philo(int argc, char **argv)
{
	t_data		data;

	parse_and_init(argc, argv, &data);
	if (!create_philo_processes(&data))
		exit_error(&data, "Error with creating philo processes");
	wait_and_handle_exit(&data);
	free_and_close(&data);
	return (0);
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
