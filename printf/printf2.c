#include <stdarg.h>
#include <unistd.h>


int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int		count_digits(long long n, int base_len)
{
	int i = 1;
	while (n >= base_len)
	{
		i++;
		n /= base_len;
	}
	return (i);
}

void	put_nbr_base(long long n, int base_len, char *base)
{
	if (n >= base_len)
		put_nbr_base(n / base_len, base_len, base);
	write(1, &base[n % base_len], 1);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int charCount = 0;
	int len, prec, flag_prec, neg, zeros, spaces, width, base_len;
	long num = 0;
	char *base, *str, *s;
	
	va_start(ap, format);
	str = (char*)format;

	while (*str)
	{
		if (*str != '%')
			charCount += write(1, str, 1);
		else
		{
			str++;
			len = 0, prec = 0, flag_prec = 0, neg = 0, zeros = 0, spaces = 0, width = 0, base_len = 0;
			//Width
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + *str - '0';
				str++;
			}
			//Precision
			if (*str == '.')
			{
				str++;
				flag_prec = 1;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 + *str - '0';
					str++;
				}
			}
			//Especificador
			if (*str == 's')
			{
				s = va_arg(ap, char *);
				if (s == ((void*)0))
					s = "(null)";
				len = ft_strlen(s);
			}
			else if (*str == 'd')
			{
				base_len = 10;
				base = "0123456789";
				num = va_arg(ap, int);
				if (num < 0)
				{
					neg = 1;
					num = -num;
				}
				len = count_digits(num, base_len) + neg;
			}
			else if (*str == 'x')
			{
				base_len = 16;
				base = "0123456789abcdef";
				num = va_arg(ap, unsigned int);
				len = count_digits(num, 16);
			}

			if (*str != 's' && flag_prec == 1 && prec > len)
				zeros = prec - len + neg;
			else if (*str == 's' && flag_prec == 1 && prec < len)
				len = prec;
			else if (flag_prec == 1 && prec == 0 && (num == 0 || *str == 's'))
				len = 0;
			spaces = width - len - zeros;
			//Imprimir espacios
			while (spaces-- > 0)
				charCount += write(1, " ", 1);
			if (neg)
				write(1, "-", 1);
			//Imprimir ceros
			while (zeros-- > 0)
				charCount += write(1, "0", 1);
			//Imprimir cosos
			if (*str == 's')
				write(1, s, len);
			else if (len > 0)
				put_nbr_base(num, base_len, base);
			charCount += len;
		}
		str++;
	}
	return (charCount);
}