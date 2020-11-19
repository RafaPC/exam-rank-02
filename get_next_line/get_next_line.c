/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:27:10 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/18 15:29:17 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *s)
{
	char *str;
	int  i = 0;
	if (!(str = malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *str;
	if (!(str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return ((c == '\0') ? &s[i] : NULL);
}

char *ft_substr(char *s, int start, int len)
{
	int i = 0;
	char *str;
	if (!(str = malloc(len + 1)))
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	// while (s[i])
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int get_next_line(char **line)
{
	static char *s;
	char buff[43];
	char *aux;
	char *temp;
	int i = 0;
	int control = 42;

	// s = NULL;
	if (line == NULL)
		return (-1);
	else if (s == NULL)   //Primera vez
	{
		control = read(3, buff, 42);
		if (control == 0)
		{
			*line = ft_strdup("");
			return (0);
		}
		else if (control < 0)
			return (-1);
		else
		{
			buff[control] = '\0';
			s = ft_strdup(buff);
		}
	}
	while (control == 42)		//Si no hay salto de línea, sigo leyendo y concatenándolo a lo que ya tengo
	{
		//Si encuentra salto de línea sale del while
		if (ft_strchr(s, '\n') != 0)
			break ;
		control = read(3, buff, 42);
		if (control < 0)
		{
			free(s);
			return (-1);
		}
		buff[control] = '\0';
		aux = ft_strjoin(s, buff);
		free(s);
		s = aux;
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
	{
		*line = ft_substr(s, 0, i);
		temp = ft_strdup(&s[i + 1]);
		free(s);
		s = temp;
	}
	else
	{
		*line = ft_strdup(s);
		free(s);
		s = NULL;
		return (0);
	}
	return (1);
}

































int get_next_line2(char **line)
{
	static char *s;
	char		*aux;
	char		buff[43];
	int control = 42;
	int i = 0;

	if (line == NULL)
		return (-1);
	else if (s == NULL)
	{
		control = read(3, buff, 42);
		if (control == 0) {
			*line = ft_strdup("");
			return (0);
		}
		else if (control < 0) {
			return (-1);
		}
		else {
			buff[control] = '\0';
			s = ft_strdup(buff);
		}
	}
	while (control == 42)
	{
		if (ft_strchr(s, '\n') != 0)
			break ;
		control = read(3, buff, 42);
		if (control < 0) {
			free(s);
			return (-1);
		}
		buff[control] = '\0';
		aux = ft_strjoin(s, buff);
		free(s);
		s = aux;
	}
	//Si llega hasta aquí es porque hay salto de línea o final de fichero
	while(s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n') {
		*line = ft_substr(s, 0, i);
		aux = ft_strdup(&s[i + 1]);
		free(s);
		s = aux;
	} else {
		*line = s;
		s = NULL;
		return (0);
	}
	return (1);
}


int		get_next_line3(char **line)
{
	static char *s;
	char		*aux;
	char		buffer[43];
	int control = 42;
	int i = 0;

	if (line == NULL)
		return (-1);
	else if (s == NULL) {
		control = read(3, buffer, 42);
		if (control == 0) {
			*line = ft_strdup("");
			return (0);
		} else if (control < 0) {
			return (-1);
		} else {
			buffer[control] = '\0';
			s = ft_strdup(buffer);
		}
	}
	while (control == 42)
	{
		if (ft_strchr(s, '\n') != NULL)
			break ;
		control = read(3, buffer, 42);
		if (control < 0) {
			free(s);
			return (-1);
		}
		buffer[control] = '\0';
		aux = ft_strjoin(s, buffer);
		free(s);
		s = aux;
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n') {
		aux = s;
		*line = ft_substr(s, 0, i);
		s = ft_strdup(&s[i + 1]);
		free(aux);
	} else {
		*line = s;
		s = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line4(char **line)
{
	static char *s;
	char		buffer[43];
	char		*aux;
	int			control = 42;
	int			i = 0;

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
	while (control == 42)
	{
		if (ft_strchr(s, '\n') != NULL)
			break ;
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
