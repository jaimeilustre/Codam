/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:42:49 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/25 12:08:25 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*allocate_str(unsigned int nb, int *strlen)
{
	int				count;
	char			*str;

	count = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		count++;
	}
	str = calloc(count + 1, sizeof(char));
	*strlen = count;
	return (str);
}

int	print_hex(unsigned int nb, int conversion)
{
	int				i;
	char			*str;
	unsigned int	temp;

	i = 0;
	temp = nb;
	if (temp == 0)
	{
		i += print_char('0');
		return (i);
	}
	str = allocate_str(nb, &i);
	if (!str)
		return (-1);
	str[i] = '\0';
	i--;
	while (temp != 0)
	{
		if ((temp % 16) < 10)
			str[i] = (temp % 16) + 48;
		else
			str[i] = (temp % 16) + conversion;
		temp /= 16;
		i--;
	}
	print_str(str);
	free (str);
	return (ft_strlen(str) - 1);
}
// #include <stdio.h>

// int main() {
//     unsigned int test_num1 = 42; // Example number in decimal (FF in hex)
//     unsigned int test_num2 = 0;    // Test case for zero

//     printf("Hexadecimal representation:\n");
//     printf("Decimal: %u -> Hex: ", test_num1);
// 	// 'A' for lowercase
//     print_hex(test_num1, 'A' - 10); 
//     printf("\n");

//     printf("Decimal: %u -> Hex: ", test_num2);
// 	// 'a' for lowercase
//     print_hex(test_num2, 'a' - 10);
//     printf("\n");

//     return (0);
// }
