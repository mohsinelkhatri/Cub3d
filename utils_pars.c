/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:32:14 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/15 11:34:50 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
