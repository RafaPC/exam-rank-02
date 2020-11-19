#include <stdlib.h>
#include <unistd.h>

int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
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

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *dest;

	if (!(dest = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	find_newline(char *s)
{
	int i = 0;
	while(s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, int len)
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
	static char	*s;
	char		buffer[43];
	char		*aux;
	int control = 42;
	int i = 0;
	
	if (line == NULL)
		return (-1);
	else if (s == NULL)
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
		s = ft_strdup(buffer);
	}

	while (find_newline(s) && control == 42)
	{
		control = read(3, buffer, 42);
		if (control < 0)
		{
			free(s);
			return (-1);
		}
		buffer[control] = '\0';
		aux = s;
		s = ft_strjoin(s, buffer);
		free(aux);
	}
	
	while (s[i] && s[i] != '\n')
		i++;
	
	if (s[i] == '\n')
	{
		*line = ft_substr(s, i);
		aux = s;
		s = ft_strdup(&s[i + 1]);
		free(aux);
	}
	else if (s[i] == '\0')
	{
		*line = s;
		s = NULL;
		return (0);
	}
	return (1);
}
