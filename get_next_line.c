/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpriyang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:31:35 by tpriyang          #+#    #+#             */
/*   Updated: 2023/07/08 16:23:06 by tpriyang         ###   ########.fr       */
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
/*char	*getting_old_line(int fd, char *old_line)
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
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	k = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ptr = (char *)malloc((i + j + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (k < i)
	{
		ptr[k] = s1[k];
		k++;
	}
	while (k < i + j)
	{
		ptr[k] = s2[k - i];
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return(0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_getting_line_from_read(int fd, char *stic_line)
{
	ssize_t	nbyte;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) + sizeof(char));
	if(!buf)
	{
		return(NULL);
	}
	nbyte = 1;
	while (!ft_strchr(stic_line, '\n') && nbyte != 0)
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if(nbyte == -1)
		{
			free(buf);
			return(NULL);
		}
		buf[nbyte] = '\0';
		stic_line = ft_strjoin(stic_line, buf);
	}
	free(buf);
	return(stic_line);
}

char	*ft_new_line_from_stic(char *stic_line)
{
	int	i;
	char	*new_line;

	i = 0;
	printf("%i\n", i);
	while (stic_line[i] && stic_line[i] != '\n')
		i++;
	new_line = (char *)malloc((i + 2) + sizeof(char));
	if (!new_line)
		return(NULL);
	if (stic_line[i] == '\n')
	{
		new_line[i] = '\n';
		new_line[i + 1] = '\0';
	}
	else
		new_line[i] = '\0';
	while(i > 0)
	{
		new_line[i] = stic_line[i];
		i--;
	}
	return(new_line);
}

char	*ft_cutting_output_line_from_stic(char *stic_line)
{
	int	i;
	int	j;
	char	*cut_line;

	i = 0;
	while (stic_line[i] && stic_line[i] != '\n')
		i++;
	cut_line = (char *)malloc((ft_strlen(stic_line - i + 1) + sizeof(char)));
	if (!cut_line)
		return(NULL);
	j = 0;
	while (stic_line[i] && stic_line[i] != '\n')
	{
		cut_line[j] = stic_line[i];
		i++;
		j++;
	}
	if (stic_line[i] == '\n')
	{
		cut_line[j] = '\n';
		cut_line[j+ 1] = '\n';
	}
	else
		cut_line[j] = '\n';
	free(stic_line);
	return(cut_line);
}

char	*get_next_line(int fd)
{
	char	*new_line;
	static char	*stic_line;

	stic_line = ft_getting_line_from_read(fd, stic_line);
	new_line = ft_new_line_from_stic(stic_line);
	stic_line = ft_cutting_output_line_from_stic(stic_line);
	return (new_line);
}

#include <fcntl.h>

int	main()
{
	int	fd;
	char	*line;
	
	fd = open("tests/simple", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return(0);
}
