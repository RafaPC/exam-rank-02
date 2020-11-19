/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieto- <rprieto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:57:01 by rprieto-          #+#    #+#             */
/*   Updated: 2020/11/18 12:22:40 by rprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>

int		char_is_repeated(char *s, char c, int index)
{
	int i = 0;
	while (i < index)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	inter(char *s1, char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (!char_is_repeated(s1, s1[i], i)) //Comprueba si cada char del primer string está repetido
		{
			//Si entra es porque encuentra que un char no está repetido
			//Entonces checkea si ese char se encuentra en el segundo string
			//Si lo encuentra, lo imprime
			if (char_is_repeated(s2, s1[i], ft_strlen(s2)))
				write(1, &s1[i], 1);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}