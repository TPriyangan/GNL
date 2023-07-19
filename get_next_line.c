/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpriyang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:31:35 by tpriyang          #+#    #+#             */
/*   Updated: 2023/07/19 15:06:04 by tpriyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*ft_getting_line_from_read(int fd, char *stic_line)
{
	ssize_t	nbyte;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		return (NULL);
	}
	nbyte = 1;
	while (!ft_strchr(stic_line, '\n') && nbyte != 0)
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nbyte] = '\0';
		stic_line = ft_strjoin(stic_line, buf);
	}
	free(buf);
	return (stic_line);
}

char	*ft_new_line_from_stic(char *stic_line)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!stic_line[i])
		return (NULL);
	while (stic_line[i] && stic_line[i] != '\n')
		i++;
	new_line = (char *)malloc((i + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (stic_line[i] && stic_line[i] != '\n')
	{
		new_line[i] = stic_line[i];
		i++;
	}
	if (stic_line[i] == '\n')
	{
		new_line[i] = stic_line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*ft_cutting_output_line_from_stic(char *stic_line)
{
	int		i;
	int		j;
	char	*cut_line;

	i = 0;
	while (stic_line[i] && stic_line[i] != '\n')
		i++;
	if (!stic_line[i])
	{
		free(stic_line);
		return (NULL);
	}
	cut_line = (char *)malloc((ft_strlen(stic_line) -i + 1) * sizeof(char));
	if (!cut_line)
		return (NULL);
	i++;
	j = 0;
	while (stic_line[i])
		cut_line[j++] = stic_line[i++];
	cut_line[j] = '\0';
	free(stic_line);
	return (cut_line);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*stic_line;

	if (BUFFER_SIZE <= 0 || !BUFFER_SIZE)
		return (0);
	if (fd < 0)
		return (0);
	stic_line = ft_getting_line_from_read(fd, stic_line);
	if (!stic_line)
		return (0);
	new_line = ft_new_line_from_stic(stic_line);
	stic_line = ft_cutting_output_line_from_stic(stic_line);
	return (new_line);
}
