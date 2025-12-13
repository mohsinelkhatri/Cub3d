/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:23:30 by melkhatr          #+#    #+#             */
/*   Updated: 2025/12/13 15:17:43 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}				t_texture;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			hex;
}				t_color;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		orientation;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_count;
}				t_map;

typedef struct s_data
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_player	player;
}				t_data;

int				parse_file(char *filename, t_data *data);
int				parse_texture(char *line, char **texture);
int				parse_color(char *line, t_color *color);
int				parse_map(int fd, t_data *data);

int				validate_map(t_data *data);
int				validate_walls(t_data *data);
int				is_valid_char(char c);
int				check_player(t_data *data);

char			*get_next_line(int fd);
char			*ft_strdup(const char *s);
char			*ft_strtrim(char *s);
int				ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
int				ft_isspace(char c);
int				is_map_line(char *line);

void			print_error(char *msg);
void			free_data(t_data *data);
void			free_split(char **split);

int				is_valid_char(char c);
void			init_data(t_data *data);
char			**realloc_map(char **map, int new_size);
int				is_player_char(char c);
void			set_north_south(t_data *data, char orientation);
void			set_east_west(t_data *data, char orientation);
void			set_player_direction(t_data *data, char orientation);
int				process_player_cell(t_data *data, int x, int y);
int				check_position_walls(t_data *data, int x, int y);
char			get_char_at(t_data *data, int x, int y);
#endif