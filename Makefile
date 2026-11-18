# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    Makefile                                               +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                   +########+               #
#                                                           +###+              #
#    Created: 2026/04/23 15:00:00 by lucas                   ##+               #
#    Updated: 2026/11/18 16:51:45 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -std=gnu17

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

LIB_SRCS = parsing/scene_parser.c parsing/parser_utils.c \
	parsing/map_parser.c parsing/error_utils.c parsing/player_parser.c \
	engine/dda_engine.c engine/line_renderer.c engine/frame_renderer.c \
	engine/player_controller.c engine/texture_manager.c \
	engine/minimap_renderer.c engine/hud_renderer.c $(PLATFORM_SRCS)
SRCS = cub3d.c $(LIB_SRCS)
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.m=.o)
LIB_OBJS = $(filter-out cub3d.o,$(OBJS))

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
	$(CC) $(CFLAGS) $(OBJS) -L$(GNL_DIR) -lgnl -L$(LIBFT_DIR) -lft \
		$(MLX_FLAGS) -o $(NAME)
ifeq ($(OS), Darwin)
	@./tools/set_icon assets/logo.png $(NAME)
endif

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

%.o: %.m
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

test_unit: $(LIB_OBJS) $(LIBFT) $(MLX_LIB) $(GNL_LIB)
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) \
		tests/unit/test_parser_unit.c $(LIB_OBJS) \
		-L$(GNL_DIR) -lgnl -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o test_unit
	./test_unit

test_func: $(LIB_OBJS) $(LIBFT) $(MLX_LIB) $(GNL_LIB)
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) \
		tests/functional/test_dda_func.c $(LIB_OBJS) \
		-L$(GNL_DIR) -lgnl -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o test_func
	./test_func

test_integ: $(NAME)
	python3 -m unittest discover -s tests/integration

test_e2e: $(NAME)
	python3 -m unittest discover -s tests/e2e

clean:
	rm -f $(OBJS)
	rm -f tools/set_icon
	@make -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/makefile.gen ] || [ "$(OS)" != "Linux" ]; then make -C $(MLX_DIR) clean; fi
	@make -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME) test_unit test_func libmlx.a libmlx.dylib
	@make -C $(LIBFT_DIR) fclean
	@make -C $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test_unit test_func test_integ test_e2e
