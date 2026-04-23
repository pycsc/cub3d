/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    cub3d.h                                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 15:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 18:00:00 by lucas                 #+                */
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

typedef struct s_data
{
	t_config	config;
	t_player	player;
	char		**map;
	t_list		*map_list;
	void		*mlx;
	void		*win;
	t_img		img;
}	t_data;

int	parse_scene(char *file, t_data *data);
int	validate_map(char **map);
int	is_config_line(char *line);
int	parse_line(char *line, t_data *data);
int	is_map_line(char *line);
int	add_map_line(char *line, t_data *data);
int	lst_to_array(t_data *data);
void	render_frame(t_data *data);

#endif
