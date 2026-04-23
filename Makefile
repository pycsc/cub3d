# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    Makefile                                               +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                   +########+               #
#                                                           +###+              #
#    Created: 2026/04/23 15:00:00 by lucas                   ##+               #
#    Updated: 2026/04/23 15:00:00 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

NAME = CUB3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
    MLX_DIR = libs/minilibx-linux
    MLX_LIB = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
else ifeq ($(OS), Darwin)
    ifeq ($(ARCH), arm64)
        MLX_DIR = libs/minilibx-mms
    else
        MLX_DIR = libs/minilibx-opengl
    endif
    MLX_LIB = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

SRCS = cub3d.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
