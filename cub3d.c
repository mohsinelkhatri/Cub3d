/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:18:39 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 15:06:15 by melkhatr         ###   ########.fr       */
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

int	parse_element(char *line, t_data *data)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line);
	if (!trimmed || trimmed[0] == '\0' || trimmed[0] == '\n')
		return (free(trimmed), 0);
	ret = 0;
	if (trimmed[0] == 'N' && trimmed[1] == 'O' && trimmed[2] == ' ')
		ret = parse_texture(trimmed + 3, &data->textures.north);
	else if (trimmed[0] == 'S' && trimmed[1] == 'O' && trimmed[2] == ' ')
		ret = parse_texture(trimmed + 3, &data->textures.south);
	else if (trimmed[0] == 'E' && trimmed[1] == 'A' && trimmed[2] == ' ')
		ret = parse_texture(trimmed + 3, &data->textures.east);
	else if (trimmed[0] == 'W' && trimmed[1] == 'E' && trimmed[2] == ' ')
		ret = parse_texture(trimmed + 3, &data->textures.west);
	else if (trimmed[0] == 'F' && trimmed[1] == ' ')
		ret = parse_color(trimmed + 2, &data->floor);
	else if (trimmed[0] == 'C' && trimmed[1] == ' ')
		ret = parse_color(trimmed + 2, &data->ceiling);
	else if (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' ')
		ret = -1;
	free(trimmed);
	return (ret);
}

int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	if (!check_file_extension(filename))
		return (print_error("Invalid file extension"), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"), 0);
	while (!all_elements_parsed(data))
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), print_error("Missing elements"), 0);
		ret = parse_element(line, data);
		free(line);
		if (ret == -1)
			break ;
	}
	if (!all_elements_parsed(data))
		return (close(fd), print_error("Missing elements"), 0);
	if (!parse_map(fd, data))
		return (close(fd), 0);
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		print_error("Usage: ./cub3d <map.cub>");
		return (1);
	}
	init_data(&data);
	if (!parse_file(argv[1], &data))
	{
		free_data(&data);
		return (1);
	}
	if (!validate_map(&data))
	{
		free_data(&data);
		return (1);
	}
	printf("Map parsed successfully!\n");
	free_data(&data);
	return (0);
}
