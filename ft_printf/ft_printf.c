/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:19:23 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/28 21:20:39 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_specifier(va_list args, const char specifier)
{
	int	len;

	len = 0;
	if (specifier == 'c')
		len += print_char(va_arg(args, int));
	else if (specifier == 's')
		len += print_str(va_arg(args, char *));
	else if (specifier == 'p')
		len += print_ptr(va_arg(args, uintptr_t));
	else if (specifier == 'd' || specifier == 'i')
		len += print_int(va_arg(args, int));
	else if (specifier == 'u')
		len += print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x')
		len += print_hex(va_arg(args, unsigned int), 0);
	else if (specifier == 'X')
		len += print_hex(va_arg(args, unsigned int), 1);
	else if (specifier == '%')
		len += print_char('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			len += check_specifier(args, str[i + 1]);
			i++;
		}
		else
			len += print_char(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

// #include "ft_printf.h"
// #include <stdio.h>

// int main()
// {
//     int len_ft, len_std;

//     // Testing %c (character)
//     char c = 'A';
//     len_ft = ft_printf("%c\n", c);
//     len_std = printf("%c\n", c);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %s (string)
//     char *str = "Hello, World!";
//     len_ft = ft_printf("Custom: %s\n", str);
//     len_std = printf("Original: %s\n", str);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %p (pointer)
//     void *ptr = (void *)str;
//     len_ft = ft_printf("Custom: %p\n", ptr);
//     len_std = printf("Original: %p\n", ptr);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %d and %i (integer)
//     int num = 1234;
//     len_ft = ft_printf("Custom: %d\n", num);
//     len_std = printf("Original: %d\n", num);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     len_ft = ft_printf("Custom: %i\n", num);
//     len_std = printf("Original: %i\n", num);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %u (unsigned integer)
//     unsigned int unum = 123456789;
//     len_ft = ft_printf("Custom: %u\n", unum);
//     len_std = printf("Original: %u\n", unum);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %x (hexadecimal, lowercase)
//     len_ft = ft_printf("Custom: %x\n", unum);
//     len_std = printf("Original: %x\n", unum);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %X (hexadecimal, uppercase)
//     len_ft = ft_printf("Custom: %X\n", unum);
//     len_std = printf("Original: %X\n", unum);
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     // Testing %% (percent sign)
//     len_ft = ft_printf("Custom: %%\n");
//     len_std = printf("Original: %%\n");
//     printf("Custom len: %d | Original len: %d\n\n", len_ft, len_std);

//     return 0;
// }
