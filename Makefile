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

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

OS := $(shell uname)
ARCH := $(shell uname -m)

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

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

SRCS = cub3d.c parsing/scene_parser.c parsing/parser_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
