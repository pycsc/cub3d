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

typedef struct s_config
{
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	int		floor_col;
	int		ceiling_col;
}	t_config;

typedef struct s_data
{
	t_config	config;
	char		**map;
	void		*mlx;
	void		*win;
}	t_data;

int	parse_scene(char *file, t_data *data);
int	validate_map(char **map);

#endif
