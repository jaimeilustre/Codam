/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:42:49 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/28 20:13:31 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned int nb)
{
	int				len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 16;
		len++;
	}
	return (len);
}

static void	convert_hex(unsigned int nb, int uppercase)
{
	if (nb >= 16)
	{
		convert_hex(nb / 16, uppercase);
		convert_hex(nb % 16, uppercase);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd((nb + '0'), 1);
		else
		{
			if (uppercase)
				ft_putchar_fd((nb - 10 + 'A'), 1);
			else
				ft_putchar_fd((nb - 10 + 'a'), 1);
		}
	}
}

int	print_hex(unsigned int nb, int uppercase)
{
	int	hex_nb_len;

	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	hex_nb_len = hex_len(nb);
	convert_hex(nb, uppercase);
	return (hex_nb_len);
}
