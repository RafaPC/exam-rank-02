#include <stdlib.h>
#include <unistd.h>

static int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

static int		ft_find_newline(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

static char	*ft_strdup(char *s)
{
	int i = 0;
	char *dest;

	if (!(dest = (char*)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0, j = 0;
	char *dest;

	if (!(dest = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1)
	{
		dest[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_substr(char *s, int len)
{
	int i = 0;
	char *dest;
	
	if (!(dest = (char*)malloc(len + 1)))
		return (NULL);
	while (s[i] && i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int get_next_line(char **line)
{
	static char *str;
	char		buffer[43];
	char		*aux;
	int control = 42;
	int i = 0;

	if (line == NULL)
		return (-1);
	else if (str == NULL)
	{
		control = read(3, buffer, 42);
		if (control < 0)
			return (-1);
		else if (control == 0)
		{
			*line = ft_strdup("");
			return (0);
		}
		buffer[control] = '\0';
		str = ft_strdup(buffer);
	}

	while (!ft_find_newline(str) && control == 42)
	{
		control = read(3, buffer, 42);
		if (control < 0)
		{
			free(str);
			return (-1);
		}
		buffer[control] = '\0';
		aux = str;
		str = ft_strjoin(str, buffer);
		free(aux);
	}

	while (str[i] && str[i] != '\n')
		i++;
	
	if (str[i] == '\n')
	{
		*line = ft_substr(str, i);
		aux = str;
		str = ft_strdup(&str[i + 1]);
		free(aux);
	}
	else
	{
		*line = str;
		str = NULL;
		return (0);
	}
	return (1);
}