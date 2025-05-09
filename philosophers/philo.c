/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 08:08:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/09 17:30:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>

void	cleaning(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!parse_args(argc, argv, &data))
		printf("Error with parsing\n");
	if (!init_data(&data))
		printf("Error with initialising\n");
	if (!init_mutex(&data))
		printf("Error with mutex\n");
	init_philos(&data);
	data.start_time = get_current_time();
	printf("Parsed arguments:\n");
	printf("  Philosophers: %d\n", data.nb_of_philos);
	printf("  Time to die: %d\n", data.time_to_die);
	printf("  Time to eat: %d\n", data.time_to_eat);
	printf("  Time to sleep: %d\n", data.time_to_sleep);
	printf("  Meals per philosopher: %d\n", data.nb_of_meals_per_philo);
	printf("\nPhilosopher struct initialized:\n");
	i = 0;
	while (i < data.nb_of_philos)
	{
		printf("  Philosopher %d:\n", data.philos[i].id);
		printf("    Left fork:  %p\n", (void *)data.philos[i].left_fork);
		printf("    Right fork: %p\n", (void *)data.philos[i].right_fork);
		printf("    Meals eaten: %d\n", data.philos[i].meals_eaten);
		i++;
	}
	cleaning(&data);
	return (0);
}
