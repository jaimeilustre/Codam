/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:42:49 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/28 10:19:40 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned int nb)
{
	int				len;

	len = 0;
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
// #include <stdio.h>

// int main() {
//     unsigned int test_num1 = 42; 
//     unsigned int test_num2 = 0;

//     printf("Hexadecimal representation:\n");
//     printf("Decimal: %u -> Hex: ", test_num1);
// 	// 'A' for lowercase
//     print_hex(test_num1, 1); 
//     printf("\n");

//     printf("Decimal: %u -> Hex: ", test_num2);
// 	// 'a' for lowercase
//     print_hex(test_num2, 0);
//     printf("\n");

//     return (0);
// }
