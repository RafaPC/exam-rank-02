#include <stdio.h>

int	ft_printf(const char *format, ...);

int main(void)
{
	// ft_printf("Hola que tal %s.\nDía:%d - Mes %d - Año %d\n", "rafa", 17, 12, 1999);
	printf("Return: %i\n", printf("%8.5d - %3.0x - hola %.0s %7.3s\n", -5, 9878545, "rafa", "prieto"));
	printf("Return: %i\n", ft_printf("%8.5d - %3.0x - hola %.0s %7.3s\n", -5, 9878545, "rafa", "prieto"));
	return 0;
}
