#include <stdlib.h>
// #include <fcntl.h>
#include <unistd.h>

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *final_str;
	int i = 0, j = 0;

	if (!(final_str = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1)
	{
		final_str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		final_str[i] = *s2;
		i++;
		s2++;
	}
	final_str[i] = '\0';
	return (final_str);
}

int		ft_strchr(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	int i = 0;
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

char	*ft_substr(char *s, int start, int len)
{
	char	*dest;
	int i = start;
	int j = 0;
	if (!(dest = (char*)malloc(len + 1)))
		return (NULL);
	
	while (s[i] && i < len)
	{
		dest[j] = s[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int		get_next_line(char **line)
{
	static char *s;
	char		buffer[43];
	char		*aux;
	int	i = 0;
	int control = 42;

	if (line == NULL)
		return (-1);
	else if (s == NULL) //Primera vez
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

	while (ft_strchr(s, '\n') == 0 && control == 42)
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
		*line = ft_substr(s, 0, i);
		aux = s;
		s = ft_strdup(&s[i + 1]);
		free(aux);
	}
	else
	{
		*line = s;
		s = NULL;
		return (0);
	}
	return (1);
}