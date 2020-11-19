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
		ft_putnbr_base(n / base_len, base_len, base);
	write(1, &base[n % base_len], 1);
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	char *s = (char*)format;
	char *string;
	char *base;
	int char_count = 0;
	int spaces, zeros, base_len, width, flag_prec, prec, neg, len;
	long long num;

	while (*s)
	{
		if (*s != '%')
			char_count += write(1, s, 1);
		else
		{
			s++;
			spaces = 0, zeros = 0, base_len = 0, num = 0, width = 0, flag_prec = 0, prec = 0, neg = 0, len = 0;
			while (*s >= '0' && *s <= '9')
			{
				width = width * 10 + *s - '0';
				s++;
			}

			if (*s == '.')
			{
				flag_prec = 1;
				s++;
				while (*s >= '0' && *s <= '9')
				{
					prec = prec * 10 + *s - '0';
					s++;
				}
			}

			//Especificadores
			if (*s == 's')
			{
				string = va_arg(ap, char *);
				if (string == NULL)
					string = "(null)";
				len = ft_strlen(string);
			}
			else if (*s == 'd')
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
			else if (*s == 'x')
			{
				num = va_arg(ap, unsigned);
				base_len = 16;
				base = "0123456789abcdef";
				len = ft_digits_base(num, base_len);
			}

			if (*s != 's' && flag_prec && prec > len)
				zeros = prec - len + neg;
			else if (*s == 's' && flag_prec && prec < len)
				len = prec;
			else if (flag_prec && prec == 0 && (*s == 's' || num == 0))
				len = 0;
			spaces = width - zeros - len;
			while (spaces-- > 0)
				char_count += write(1, " ", 1);
			
			if (neg)
				write(1, "-", 1);
			
			while (zeros-- > 0)
				char_count += write(1, "0", 1);
			
			if (*s == 's')
				write(1, string, len);
			else if (len > 0)
				ft_putnbr_base(num, base_len, base);
			
			char_count += len;
		}
		s++;
	}
	return (char_count);
}