# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 13:17:26 by melkhatr          #+#    #+#              #
#    Updated: 2025/12/15 11:34:15 by melkhatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = cub3d.c \
       utils_pars.c \
       check_pars.c \
       pars_texture.c \
       pars_map.c \
       valid_map.c \
       ft_atoi.c \
       ft_split.c \
       initial.c\
       utils_libft.c \
       utils_sets.c \
       gnl.c \
       utils_valid.c \
       clean.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re