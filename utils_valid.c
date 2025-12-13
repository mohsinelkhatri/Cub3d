/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:01:35 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 15:21:45 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	get_char_at(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map.height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map.grid[y]))
		return (' ');
	return (data->map.grid[y][x]);
}

int	check_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (is_player_char(data->map.grid[y][x]))
				process_player_cell(data, x, y);
			x++;
		}
		y++;
	}
	if (data->map.player_count != 1)
		return (print_error("Map must have exactly one player"), 0);
	return (1);
}

int	validate_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == '0')
			{
				if (!check_position_walls(data, x, y))
					return (print_error("Map not closed by walls"), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
