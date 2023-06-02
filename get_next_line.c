/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpriyang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:31:35 by tpriyang          #+#    #+#             */
/*   Updated: 2023/06/02 13:55:43 by tpriyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
 # define BUFFER_SIZE 42
#endif

//Fonction pour ecrire null
char	*writing_null(void)
{
	write(1, "null", 4);
	return ("null");
}

//Foncton pour recuperer la ligne a AFFICHER :
//fd en parametre | cree une nouvelle string str 
char	*getting_new_line(int fd)
{
	char		*str;
	ssize_t		read_bytes;
	int		i;

	i = 0;
	str = (char *)malloc((BUFFER_SIZE + 1) + sizeof(char));
	if (!str)
		return (writing_null());
	read_bytes = 1;
	read_bytes = read(fd, str, BUFFER_SIZE);
	if (read_bytes == -1)
	{
		free(str);
		return(writing_null());
	}
	while (str[i] && str[i] != '\n')
	{
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*writing_old_line(char *new_str)
{
	int	i;
	char	*str;

	i = 0;
	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return(writing_null());
	while (i < BUFFER_SIZE && str[i])
	{
		str[i] = new_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*old_line;

	new_line = getting_new_line(fd);
	printf("%s\n" , new_line);
	old_line = writing_old_line(new_line);
	printf("%s\n" , old_line);
	free(new_line);
	return (old_line);
}

int	main()
{
	char	*line;
	int	i;
	int	fd_int;

	fd_int = open("tests/test.txt", O_RDONLY);
	i = 0;
	while(i < 5)
	{
		line = get_next_line(fd_int);
		printf("line [%02d]: %s" , i ,line);
		free(line);
	i++;
	}
	close(fd_int);
	return(0);
}
