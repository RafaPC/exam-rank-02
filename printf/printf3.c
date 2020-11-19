#include <stdarg.h>
#include <unistd.h>


int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_digits_base(long long num, int base_len)
{
	int i = 1;
	while (num >= base_len)
	{
		num /= base_len;
		i++;
	}
	return (i);
}

void	putnbr_base(long long num, int base_len, char *base)
{
	if (num >= base_len)
		putnbr_base(num/base_len, base_len, base);
	write(1, &base[num % base_len],1);
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int char_count, zeros, spaces, width, flag_prec, prec, base_len, len, neg;
	char *str, *s, *base;
	long long num;
	str = (char*)format;
	char_count = 0;
	num = 0;
	while (*str)
	{
		if (*str != '%')
			char_count += write(1, str, 1);
		else
		{
			num = 0, zeros = 0, spaces = 0,width = 0, neg = 0,
			flag_prec = 0, prec = 0, base_len = 0, len = 0;
			str++;
			//width
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
			//Specifiers
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
			}else if (*str == 'x'){
				num = va_arg(ap, unsigned int);
				base_len = 16;
				base = "0123456789abcdef";
				len = ft_digits_base(num, base_len);
			}
			//Comprobaciones
			if (*str != 's' && flag_prec == 1 && prec > len)
				zeros = prec - len + neg;
			else if (*str == 's' && flag_prec == 1 && prec < len)
				len = prec;
			else if (flag_prec == 1 && prec == 0 && (*str == 's' || num == 0))
				len = 0;
			spaces = width - zeros - len;
			while (spaces-- > 0)
				char_count += write(1, " ", 1);
			if (neg == 1)
				write(1, "-", 1);
			while (zeros-- > 0)
				char_count += write(1, "0", 1);
			if (*str == 's')
				write(1, s, len);
			else if (len > 0)
				putnbr_base(num, base_len, base);
			char_count += len;
		}
		str++;
	}
	va_end(ap);
	return (char_count);
}