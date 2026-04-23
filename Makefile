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
GNL_LIB = $(GNL_DIR)/get_next_line.a

# ... (rest of Makefile variables)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(GNL_LIB):
	@make -C $(GNL_DIR) bonus

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB) $(GNL_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lget_next_line $(MLX_FLAGS) -o $(NAME)

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
