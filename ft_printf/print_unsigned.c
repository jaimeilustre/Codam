/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:36:12 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/28 20:25:32 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_number(unsigned int nb)
{
	if (nb >= 10)
		print_number(nb / 10);
	ft_putchar_fd((nb % 10) + '0', 1);
}
static int	nb_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

int	print_unsigned(unsigned int nb)
{
	int	len;

	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	print_number(nb);
	len = nb_len(nb);
	return (len);
}
