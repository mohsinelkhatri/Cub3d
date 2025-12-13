/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:20:15 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 14:47:05 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *line, char **texture)
{
	char	*trimmed;
	char	*path;
	int		fd;
	int		i;

	if (*texture != NULL)
		return (print_error("Duplicate texture"), 0);
	trimmed = ft_strtrim(line);
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), print_error("Empty texture path"), 0);
	i = 0;
	while (trimmed[i] && trimmed[i] != ' ' && trimmed[i] != '\n')
		i++;
	trimmed[i] = '\0';
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
		return (free(trimmed), print_error("Cannot open texture file"), 0);
	close(fd);
	path = ft_strdup(trimmed);
	free(trimmed);
	if (!path)
		return (print_error("Memory allocation failed"), 0);
	*texture = path;
	return (1);
}

int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

int	parse_rgb_values(char **rgb, t_color *color)
{
	int	i;

	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (print_error("Invalid RGB format"), 0);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (!validate_rgb_value(color->r) || !validate_rgb_value(color->g)
		|| !validate_rgb_value(color->b))
		return (print_error("RGB values must be 0-255"), 0);
	color->hex = (color->r << 16) | (color->g << 8) | color->b;
	return (1);
}

int	validate_rgb_string(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		else if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n'
			&& str[i] != '\t')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

int	parse_color(char *line, t_color *color)
{
	char	*trimmed;
	char	**rgb;
	int		ret;

	if (color->r != -1)
		return (print_error("Duplicate color"), 0);
	trimmed = ft_strtrim(line);
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), print_error("Empty color"), 0);
	if (!validate_rgb_string(trimmed))
	{
		free(trimmed);
		return (print_error("Invalid color format"), 0);
	}
	rgb = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb)
		return (print_error("Memory allocation failed"), 0);
	ret = parse_rgb_values(rgb, color);
	free_split(rgb);
	return (ret);
}
