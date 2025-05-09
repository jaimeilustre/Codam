/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:55:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/09 17:29:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>

struct	s_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals_per_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_mutex;
	struct s_philo	*philos;
	int				deaths;
	int				start_time;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				time_since_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

bool	valid_int(const char *str);
long	ft_strtol(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
size_t	get_current_time(void);
int		ft_usleep(size_t ms);

bool	initialize_args(char *arg, int index, t_data *data);
bool	parse_args(int argc, char **arg, t_data *data);
bool	init_mutex(t_data *data);
bool	init_data(t_data *data);
void	init_philos(t_data *data);

void	cleaning(t_data *data);
int		main(int argc, char **argv);

void	print_message(t_philo *philo, char *msg);
void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	return_forks(t_philo *philo);
void	sleep(t_philo *philo);
void	*routine(void *arg);

bool	create_thread(t_data *data);
