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

GNL_DIR = libs/get_next_line
GNL_LIB = $(GNL_DIR)/libgnl.a
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

ifeq ($(OS), Linux)
    MLX_DIR = libs/minilibx-linux
    MLX_LIB = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
else ifeq ($(OS), Darwin)
    ifeq ($(ARCH), arm64)
        MLX_DIR = libs/minilibx-mms
				MLX_LIB = $(MLX_DIR)/libmlx.dylib
    else
        MLX_DIR = libs/minilibx-opengl
				MLX_LIB = $(MLX_DIR)/libmlx.a
    endif
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

SRCS = cub3d.c parsing/scene_parser.c parsing/parser_utils.c parsing/map_parser.c engine/raycasting_engine.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(GNL_LIB):
	@make -C $(GNL_DIR) bonus

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB) $(GNL_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@make -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(GNL_DIR) fclean

re: fclean all
