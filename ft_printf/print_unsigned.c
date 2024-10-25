/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:36:12 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/25 09:39:31 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_nb(unsigned int nb);

static void 	print_number(unsigned int nb)
{
	if (nb >= 10)
		print_unsigned_nb(nb / 10);
	else if (nb < 10)
	{
		ft_putchar_fd(nb + '0', 1);
		return ;
	}
	ft_putchar_fd((nb % 10) + '0', 1);
}

int	print_unsigned_nb(unsigned int nb)
{
	unsigned int	len;

	print_number(nb);
	len = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

// #include <stdio.h>

// int main() {
//     unsigned int test_num1 = -42;

//     printf("Decimal: %u\n ", test_num1);
//     print_unsigned_nb(test_num1); 

//     return (0);
// }