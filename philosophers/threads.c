/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 10:35:34 by jilustre      #+#    #+#                 */
/*   Updated: 2025/04/29 09:59:35 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*Basic example of threads*/

void	*say_hello()
{
	printf("Hello from a thread!\n");
	return (NULL);
}

// int	main(void)
// {
// 	pthread_t	thread;
	
// 	pthread_create(&thread, NULL, say_hello, NULL);
// 	pthread_join(thread, NULL);
// 	// pthread_detach(thread);
// 	printf("Main thread is done!\n");
// 	return (0);
// }

/*Basic example of mutexes*/

/*Without mutex; multiple threads access and modify shared data 
at the same time, causing unexpected behavior (corruption, crashes, wrong results)*/

// int	counter = 0; // Shared resource

// void	*increment()
// {
// 	int	i;

// 	i = 0;
// 	while (i < 1000000)
// 	{
// 		counter++;
// 		i++;
// 	}
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_t	t1;
// 	pthread_t	t2;
	
// 	pthread_create(&t1, NULL, increment, NULL);
// 	pthread_create(&t2, NULL, increment, NULL);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	printf("Final counter: %d\n", counter);
// 	return (0);
// }

// /*With mutex; only one thread at a time can modify counter*/

int counter = 0;
pthread_mutex_t lock;

void	*increment()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&lock); // Locks the resource so that only one thread can enter;
		counter++; // Safe modification
		pthread_mutex_unlock(&lock); // Unlocks the resource so that another thread can use it;
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	
	pthread_mutex_init(&lock, NULL);
	pthread_create(&t1, NULL, increment, NULL);
	pthread_create(&t2, NULL, increment, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&lock);
	printf("Final counter: %d\n", counter);
	return (0);
}

