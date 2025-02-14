/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 11:22:44 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	static const int	max_size = 11;
	char				nbr[11];
	unsigned int		un;
	int					i;

	if (n == 0)
		return (write (fd, "0", 1));
	i = max_size;
	if (n < 0)
		un = ~n + 1;
	else
		un = n;
	while (un != 0)
	{
		nbr[--i] = '0' + (un % 10);
		un /= 10;
	}
	if (n < 0)
		nbr[--i] = '-';
	return (write(fd, &nbr[i], max_size - i));
}
