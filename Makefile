# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    Makefile                                               +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                   +########+               #
#                                                           +###+              #
#    Created: 2026/04/23 15:00:00 by lucas                   ##+               #
#    Updated: 2026/05/09 15:45:00 by lucas                  #+                 #
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
    PLATFORM_SRCS = engine/linux_icon.c
    SET_ICON_TOOL =
else ifeq ($(OS), Darwin)
    ifeq ($(ARCH), arm64)
        MLX_DIR = libs/minilibx-mms
				MLX_LIB = $(MLX_DIR)/libmlx.dylib
    else
        MLX_DIR = libs/minilibx-opengl
				MLX_LIB = $(MLX_DIR)/libmlx.a
    endif
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    PLATFORM_SRCS = engine/macos_icon.m
    SET_ICON_TOOL = tools/set_icon
endif

SRCS = cub3d.c \
			 parsing/scene_parser.c \
			 parsing/parser_utils.c \
			 parsing/map_parser.c \
			 engine/dda_engine.c \
			 engine/line_renderer.c \
			 engine/frame_renderer.c \
			 engine/player_controller.c \
			 engine/texture_manager.c \
			 engine/minimap_renderer.c \
			 engine/hud_renderer.c \
			 $(PLATFORM_SRCS)
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.m=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(GNL_LIB):
	@make -C $(GNL_DIR) bonus

$(SET_ICON_TOOL): tools/set_icon.m
	@$(CC) -framework AppKit tools/set_icon.m -o tools/set_icon

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB) $(GNL_LIB) $(SET_ICON_TOOL)
	@cp $(MLX_LIB) .
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl $(MLX_FLAGS) -o $(NAME)
ifeq ($(OS), Darwin)
	@./tools/set_icon assets/logo.png $(NAME)
endif

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

%.o: %.m
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f tools/set_icon
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@make -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(GNL_DIR) fclean

re: fclean all
