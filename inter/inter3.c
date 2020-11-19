#include <unistd.h>

int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int		char_is_repeated(char *s, char c, int index)
{
	int i = 0;
	
	while (s[i] && i < index)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	
	return (0);
}

void ft_inter(char *s1, char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (!char_is_repeated(s1, s1[i], i))
		{
			if (char_is_repeated(s2, s1[i], ft_strlen(s2)))
				write(1, &s1[i], 1);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}