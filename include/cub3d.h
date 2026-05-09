/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    cub3d.h                                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 15:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:30:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <string.h>

# include "libft.h"

# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
# else
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
# endif

typedef struct s_config
{
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	int		floor_col;
	int		ceiling_col;
}	t_config;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_dda
{
	double	rx;
	double	ry;
	int		map[2];
	double	sd[2];
	double	dd[2];
	int		step[2];
	int		side;
	double	pwd;
	int		hit_coin;
	double	coin_pwd;
	double	coin_wall_x;
}	t_dda;

typedef struct s_data
{
	t_config	config;
	t_player	player;
	char		**map;
	t_list		*map_list;
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		tex[4];
	int			keys[65536];
	int			health;
	int			ammo;
	int			score;
	long long	frame;
}	t_data;

int		parse_scene(char *file, t_data *data);
int		validate_map(t_data *data);
int		is_config_line(char *line);
int		parse_line(char *line, t_data *data);
int		is_map_line(char *line);
int		add_map_line(char *line, t_data *data);
int		lst_to_array(t_data *data);
int		init_player(t_data *data);
int		update_game(t_data *data);
int		load_textures(t_data *data);
void	render_frame(t_data *data);
void	move_player(t_data *data, double dx, double dy);
void	rotate_player(t_data *data, double angle);
void	draw_minimap(t_data *data);
void	draw_hud(t_data *data);
void	set_platform_icon(const char *path);
void	spawn_coin(t_data *data);
void	print_error(char *msg);

#endif
