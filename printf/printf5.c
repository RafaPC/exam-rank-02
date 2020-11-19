#include <unistd.h>
#include <stdarg.h>

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}


int		ft_digits_base(long long n, int base_len)
{
	int i = 1;
	while (n >= base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

void	ft_putnbr_base(long long n, int base_len, char *base)
{
	if (n >= base_len)
		ft_putnbr_base(n/base_len, base_len, base);
	write(1, &base[n % base_len], 1);
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	char *str = (char*)format;
	int char_count = 0;

	char *s, *base;
	int width, flag_prec, prec, spaces, zeros, len, neg, base_len;
	long long num;

	while (*str)
	{
		if (*str != '%')
			char_count += write(1, str, 1);
		else
		{
			str++;
			width = 0, flag_prec = 0, prec = 0, spaces = 0, zeros = 0, len = 0, neg = 0, base_len = 0, num = 0;

			//width
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + *str - '0';
				str++;
			}
			//precision
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
			//specifiers
			if (*str == 's')
			{
				s = va_arg(ap, char *);
				if (s == NULL)
					s = "(null)";
				len = ft_strlen(s);
			}
			else if (*str == 'd')
			{
				num = va_arg(ap, int);
				base_len = 10;
				base = "0123456789";
				if (num < 0)
				{
					neg = 1;
					num = -num;
				}
				len = ft_digits_base(num, base_len) + neg;
			}
			else if (*str == 'x')
			{
				num = va_arg(ap, unsigned);
				base_len = 16;
				base = "0123456789abcdef";
				len = ft_digits_base(num, base_len);
			}

			if (*str != 's' && flag_prec && prec > len)
				zeros = prec - len + neg;
			else if (*str == 's' && flag_prec && prec < len)
				len = prec;
			else if (flag_prec && prec == 0 && (num == 0 || *str == 's'))
				len = 0;
			spaces = width - zeros - len;

			//Imprimir
			while (spaces-- > 0)
				char_count += write(1, " ", 1);
			if (neg)
				write(1, "-", 1);
			while (zeros-- > 0)
				char_count += write(1, "0", 1);
			
			if (*str == 's')
				write(1, s, len);
			else if (len > 0)
				ft_putnbr_base(num, base_len, base);
			char_count += len;
		}
	str++;
	}
	va_end(ap);
	return (char_count);
}