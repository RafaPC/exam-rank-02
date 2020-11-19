#include <unistd.h>


int		ft_char_is_repeated(char *s, char c, int index)
{
	int i = 0;

	while(s[i] && i < index)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_union(char *s1, char *s2)
{
	int i = 0;
	int j = 0;

	while (s1[i])
	{
		if (!ft_char_is_repeated(s1, s1[i], i))
			write(1, &s1[i], 1);
		i++;
	}

	while (s2[j])
	{
		if (!ft_char_is_repeated(s1, s2[j], i) && !ft_char_is_repeated(s2, s2[j], j))
			write(1, &s2[j], 1);
		j++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return(0);
}