/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:22:33 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 15:25:03 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_buffer(int fd, char *buffer, int *buffer_pos, int *buffer_read)
{
	if (*buffer_pos >= *buffer_read)
	{
		*buffer_read = read(fd, buffer, BUFFER_SIZE);
		*buffer_pos = 0;
		if (*buffer_read <= 0)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	buffer_pos;
	static int	buffer_read;
	char		temp[BUFFER_SIZE * 2];
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	len = 0;
	while (1)
	{
		if (!read_buffer(fd, buffer, &buffer_pos, &buffer_read))
			break ;
		temp[len] = buffer[buffer_pos++];
		if (temp[len] == '\n' || ++len >= BUFFER_SIZE * 2 - 1)
		{
			len++;
			break ;
		}
	}
	if (len == 0)
		return (NULL);
	temp[len] = '\0';
	return (ft_strdup(temp));
}
