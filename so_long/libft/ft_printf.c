/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:19:23 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/29 16:26:51 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_specifier(va_list args, const char specifier)
{
	int	len;

	len = 0;
	if (specifier == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (specifier == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (specifier == 'p')
		len += ft_print_ptr(va_arg(args, uintptr_t));
	else if (specifier == 'd' || specifier == 'i')
		len += ft_print_int(va_arg(args, int));
	else if (specifier == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x')
		len += ft_print_hex(va_arg(args, unsigned int), 0);
	else if (specifier == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), 1);
	else if (specifier == '%')
		len += ft_print_char('%');
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
			len += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
