/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:21:55 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 15:21:32 by melkhatr         ###   ########.fr       */
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
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	check_position_walls(t_data *data, int x, int y)
{
	if (get_char_at(data, x - 1, y) == ' ' || get_char_at(data, x + 1, y) == ' '
		|| get_char_at(data, x, y - 1) == ' ' || get_char_at(data, x, y
			+ 1) == ' ')
		return (0);
	return (1);
}

int	validate_map(t_data *data)
{
	if (!check_player(data))
		return (0);
	if (!validate_walls(data))
		return (0);
	return (1);
}
