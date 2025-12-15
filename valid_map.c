/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:21:55 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/15 11:35:15 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_player_cell(t_data *data, int x, int y)
{
	data->map.player_count++;
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	set_player_direction(data, data->map.grid[y][x]);
	data->map.grid[y][x] = '0';
	if (!check_position_walls(data, x, y))
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0' || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_position_walls(t_data *data, int x, int y)
{
	char	c;

	c = get_char_at(data, x - 1, y);
	if (c == ' ' || c == '\0')
		return (0);
	c = get_char_at(data, x + 1, y);
	if (c == ' ' || c == '\0')
		return (0);
	c = get_char_at(data, x, y - 1);
	if (c == ' ' || c == '\0')
		return (0);
	c = get_char_at(data, x, y + 1);
	if (c == ' ' || c == '\0')
		return (0);
	return (1);
}

int	validate_map_characters(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (!is_valid_char(data->map.grid[y][x]))
				return (print_error("Invalid character in map"), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_data *data)
{
	if (!validate_map_characters(data))
		return (0);
	if (!check_player(data))
		return (0);
	if (!validate_walls(data))
		return (0);
	return (1);
}
