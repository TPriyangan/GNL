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
/*char	*writing_null(void)
{
	write(1, "null", 4);
	return ("null");}*/

//Foncton pour recuperer la ligne a AFFICHER :
//fd en parametre | cree une nouvelle string str 
char	*getting_old_line(int fd, char *old_line)
{
	char		*str;
	ssize_t		read_bytes;
	int		i;

	i = 0;
	str = (char *)malloc((BUFFER_SIZE + 1) + sizeof(char));
	if (!str)
		return (NULL);
	read_bytes = 1;
	read_bytes = read(fd, str, BUFFER_SIZE);
	if (read_bytes == -1)
	{
		free(str);
		return(NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	str[i] = '\0';
	old_line = ft_strjoin(old_line, str);
	free(str);
	return (old_line);
}

char	*making_new_line(char *old_line)
{
	char	*str;
	int	i;
	
	i = 0;
	while (old_line[i] && old_line[i] != '\n')
	{
		i++;
	}
	i = 0;
	str = (char*)malloc((i+1)*sizeof(char));
	if (!str)
	return (NULL);
	while (old_line[i] && old_line[i] != '\n')
	{
		str[i] = old_line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*updating_old_line(char *old_line)
{
	int	i;
	int	j;
	int	length;
	char	*str;
	
	
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*old_line;

	old_line = getting_old_line(fd, old_line);
	printf("%s\n" , new_line);
	new_line = making_new_line(old_line);
	printf("%s\n" , old_line);
	old_line = updating_old_line(old_line, new_line);
	return (new_line;
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
