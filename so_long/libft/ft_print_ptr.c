/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:57:18 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/29 11:10:09 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptr_len(uintptr_t nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		len++;
	}
	return (len);
}

static void	convert_ptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		convert_ptr(nb / 16);
		convert_ptr(nb % 16);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd((nb + '0'), 1);
		else
			ft_putchar_fd((nb - 10 + 'a'), 1);
	}
}

int	ft_print_ptr(uintptr_t ptr)
{
	int	hex_ptr_len;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	hex_ptr_len = ptr_len(ptr);
	convert_ptr(ptr);
	return (2 + hex_ptr_len);
}
