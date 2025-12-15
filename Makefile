# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 13:17:26 by melkhatr          #+#    #+#              #
#    Updated: 2025/12/15 11:45:46 by melkhatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
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

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${SRCS} -o ${NAME}

clean:
	@${RM} ${OBJS}
 
fclean:
	@${RM} ${OBJS}
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re