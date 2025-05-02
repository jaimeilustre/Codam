/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:55:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/02 08:47:28 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_data
{
	int			nb_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_of_meals_per_philo;
	int			nb_of_forks;
	int			deaths;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	int			time_since_last_meal;
	pthread_t	*left_fork;
	pthread_t	*right_fork;
}	t_philo;

long	ft_strtol(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
bool	parse_args(char *arg, int index, t_data *data);
int		main(int argc, char **argv);
