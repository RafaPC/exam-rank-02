/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_andes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:55:46 by aiglesia          #+#    #+#             */
/*   Updated: 2020/11/18 16:52:10 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>

int print_text(char **formatString, int *i)
{
	while (**formatString)
	{
		if (**formatString == '%')
			return((int)(*formatString = *formatString + 1));
		*i += 1;
		write(1, *formatString, 1);
		*formatString = *formatString + 1;
	}
	return(0);
}

int print_string(char *str)
{
	int i;

	i = 0;
	if (!str)
		return(print_string("(NULL)"));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

void print_number(long int nb, int *i)
{
	long int	n_copy;
	char		c;

	n_copy = nb;
	if (n_copy < 0)
	{
		n_copy = -n_copy;
		*i += write(1, "-", 1);
	}
	if (n_copy > 9)
	{
		print_number(n_copy / 10, i);
		c = n_copy % 10 + 48;
	}
	else
		c = n_copy + 48;
	*i += write(1, &c, 1);
}

void print_hex(unsigned long nb, int *i, char x)
{
	char		*hex_characters;

	hex_characters = (x == 'x')
	? "0123456789abcdef" : "0123456789ABCDEF";
	if (nb > 15)
	{
		print_hex(nb / 16, i, x);
		write(1, &hex_characters[nb % 16], 1);
	}
	else
		write(1, &hex_characters[nb], 1);
	(*i)++;
}

void print_ptr(void *ptr, int *i)
{
	*i += print_string("0x");
	print_hex((long)ptr, i, 'x');
}

void print_char(char c, int *i)
{
	*i += write(1, &c, 1);
}

int print_conversion(va_list ap, char **formatString)
{
	int i;

	i = 0;
	if (**formatString == 's')
		i = print_string(va_arg(ap, char *));
	if (**formatString == 'd' || **formatString == 'i')
		print_number(va_arg(ap, int), &i);
	if (**formatString == 'u')
		print_number(va_arg(ap, unsigned int), &i);
	if (**formatString == 'x' || **formatString == 'X')
		print_hex(va_arg(ap, unsigned int), &i, **formatString);
	if (**formatString == 'p')
		print_ptr(va_arg(ap, void *), &i);
	if (**formatString == 'c')
		print_char(va_arg(ap, int), &i);
	if (**formatString == '%')
		print_char('%', &i);
	*formatString = *formatString + 1;
	return(i);
}

int	ft_printf11(char *formatString, ...)
{
	va_list			ap;
	int i;
	va_start(ap, formatString);

	i = 0;
	while (print_text(&formatString, &i))
		i += print_conversion(ap, &formatString);
	va_end(ap);
	return(i);
}

int	ft_printf2(char *formatString, ...)
{
	va_list			ap;
	int i;
	va_start(ap, formatString);

	i = 0;
	// while (print_text(&formatString, &i))
	// 	i += print_conversion(ap, &formatString);
while (*formatString)
{
	if (*formatString == '%')
		print_conversion(ap, &formatString);
	else
		i += write(1, formatString, 1);
	
}
	va_end(ap);
	return(i);
}