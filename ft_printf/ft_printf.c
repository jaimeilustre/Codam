/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:19:23 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/29 10:11:35 by jilustre         ###   ########.fr       */
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

// #include <stdio.h>

// int	main(void)
// {
// 	int				len_ft;
// 	int				len_std;
// 	char			c = 'j';
// 	char			*str = "Hello, World!";
// 	void			*ptr = str;
// 	int				nb = 0;
// 	unsigned int	unb = 42;

// 	// Testing %c (character)
// 	len_ft = ft_printf("%c\n", c);
// 	len_std = printf("%c\n", c);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %s (string)
// 	len_ft = ft_printf("%s\n", str);
// 	len_std = printf("%s\n", str);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing if string is NULL
// 	len_ft = ft_printf("%s\n", NULL);
// 	len_std = printf("%s\n", NULL);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %p (pointer)
// 	len_ft = ft_printf("%p\n", ptr);
// 	len_std = printf("%p\n", ptr);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing if pointer is NULL;
// 	len_ft = ft_printf("%p\n", NULL);
// 	len_std = printf("%p\n", NULL);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %d and %i (integer)
// 	len_ft = ft_printf("%d\n", nb);
// 	len_std = printf("%d\n", nb);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	len_ft = ft_printf("%i\n", nb);
// 	len_std = printf("%i\n", nb);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %u (unsigned integer)
// 	len_ft = ft_printf("%u\n", unb);
// 	len_std = printf("%u\n", unb);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %x (hexadecimal, lowercase)
// 	len_ft = ft_printf("%x\n", unb);
// 	len_std = printf("%x\n", unb);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %X (hexadecimal, uppercase)
// 	len_ft = ft_printf("%X\n", unb);
// 	len_std = printf("%X\n", unb);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing %% (percent sign)
// 	len_ft = ft_printf("%%\n");
// 	len_std = printf("%%\n");
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing multiple specifiers (different)
// 	len_ft = ft_printf("%c, %s, %p, %d, %x, %X\n", c, str, ptr, nb, unb, unb);
// 	len_std = printf("%c, %s, %p, %d, %x, %X\n", c, str, ptr, nb, unb, unb);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing multiple specifiers (same)
// 	len_ft = ft_printf("%s, %s, %s, %s, %s\n", str, str, str, str, str);
// 	len_std = printf("%s, %s, %s, %s, %s\n", str, str, str, str, str);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	// Testing NULL
// 	len_ft = ft_printf(NULL);
// 	len_std = printf(NULL);
// 	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

// 	return (0);
// }
