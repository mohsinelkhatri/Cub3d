/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:20:15 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/15 11:35:03 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_invalid_spacing(char *str)
{
	int	i;
	int	space_count;

	i = 0;
	space_count = 0;
	while (str[i])
	{
		if (check_space_sequence(str, i, space_count))
			return (1);
		if (str[i] == ' ' || str[i] == '\t')
			space_count++;
		else if (str[i] != '\n')
			space_count = 0;
		i++;
	}
	return (0);
}

static char	*extract_path(char *str)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	len = 0;
	while (str[i + len] && str[i + len] != ' ' && str[i + len] != '\t'
		&& str[i + len] != '\n')
		len++;
	if (len == 0)
		return (NULL);
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	len = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		path[len++] = str[i++];
	path[len] = '\0';
	return (path);
}

static int	has_trailing_content(char *str, char *path)
{
	int	i;
	int	path_len;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	path_len = ft_strlen(path);
	i += path_len;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	parse_texture(char *line, char **texture)
{
	char	*path;
	int		fd;

	if (*texture != NULL)
		return (print_error("Duplicate texture"), 0);
	if (has_invalid_spacing(line))
		return (print_error("Invalid texture path format"), 0);
	path = extract_path(line);
	if (!path || path[0] == '\0')
		return (free(path), print_error("Empty texture path"), 0);
	if (has_trailing_content(line, path))
		return (free(path), print_error("Invalid content after texture"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(path), print_error("Cannot open texture file"), 0);
	close(fd);
	*texture = path;
	return (1);
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
