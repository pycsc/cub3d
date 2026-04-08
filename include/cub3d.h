/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    cub3d.h                                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/08 06:25:19 by lucas                  ##+              */
/*    Updated: 2026/04/08 06:25:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

/* Main header file for cub3D */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"

/* Data structure for game state */
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			img_width;
	int			img_height;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	/* Map data */
	char		**map;
	int			map_width;
	int			map_height;

	/* Player position and direction */
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	/* Textures */
	void		*north_texture;
	void		*south_texture;
	void		*west_texture;
	void		*east_texture;

	/* Colors */
	int			floor_color;
	int			ceiling_color;

	/* Movement flags */
	bool		forward;
	bool		backward;
	bool		left;
	bool		right;
}	t_data;

/* Parsing functions */
int			parse_scene(char *path, t_data *data);
int			parse_map_line(char *line, t_data *data, int line_num);
int			parse_textures(char *line, t_data *data);
int			parse_colors(char *line, t_data *data);
int			check_map_validity(t_data *data);

/* Rendering functions */
int			init_mlx_win(t_data *data);
int			start_rendering(t_data *data);
void		raycasting(t_data *data);
int			draw_line(t_data *data, double x1, double y1, double x2, double y2, int color);
int			get_texture_color(void *texture, int x, int y);

/* Cleanup function */
int			cleanup(t_data *data, int exit_code);

#endif
