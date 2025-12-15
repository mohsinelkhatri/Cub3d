/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:28:15 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/15 11:35:41 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

int	all_elements_parsed(t_data *data)
{
	if (!data->textures.north || !data->textures.south || !data->textures.east
		|| !data->textures.west)
		return (0);
	if (data->floor.r == -1 || data->ceiling.r == -1)
		return (0);
	return (1);
}

int	skip_to_map(int fd, t_data *data)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (print_error("No map found"), 0);
		ret = parse_element(line, data);
		free(line);
		if (ret == 0)
			return (0);
		if (ret == -1)
			return (1);
	}
}

int	check_space_sequence(char *str, int i, int space_count)
{
	if (str[i] == ' ' || str[i] == '\t')
	{
		space_count++;
		if (space_count > 1)
			return (1);
	}
	else if (str[i] != '\n')
	{
		if (space_count > 0 && i > 0)
			return (1);
		space_count = 0;
	}
	return (0);
}
