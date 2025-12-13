/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:21:20 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 15:09:40 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_line_length(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

int	copy_line_to_map(char *line, char *map_line, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		map_line[i] = line[i];
		i++;
	}
	map_line[len] = '\0';
	return (1);
}

int	add_map_line(t_data *data, char *line)
{
	char	**new_map;
	char	*map_line;
	int		len;

	len = get_line_length(line);
	if (len > data->map.width)
		data->map.width = len;
	new_map = realloc_map(data->map.grid, data->map.height + 2);
	if (!new_map)
		return (print_error("Memory allocation failed"), 0);
	data->map.grid = new_map;
	map_line = malloc(len + 1);
	if (!map_line)
		return (print_error("Memory allocation failed"), 0);
	copy_line_to_map(line, map_line, len);
	data->map.grid[data->map.height] = map_line;
	data->map.grid[data->map.height + 1] = NULL;
	data->map.height++;
	return (1);
}

int	handle_map_line(t_data *data, char *line, int *map_started)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		if (!add_map_line(data, line))
		{
			free(line);
			return (0);
		}
	}
	else if (*map_started && line[0] != '\n' && line[0] != '\0')
	{
		free(line);
		print_error("Invalid character in map");
		return (0);
	}
	return (1);
}

int	parse_map(int fd, t_data *data)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!handle_map_line(data, line, &map_started))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	if (data->map.height == 0)
		return (print_error("No map found"), 0);
	return (1);
}
