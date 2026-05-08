/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    texture_manager.c                                     +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 07:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 07:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static int	load_tex(t_data *data, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (print_error("Failed to load texture file"), 1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, \
		&tex->line_length, &tex->endian);
	return (0);
}

int	load_textures(t_data *data)
{
	if (load_tex(data, &data->tex[0], data->config.no_tex))
		return (1);
	if (load_tex(data, &data->tex[1], data->config.so_tex))
		return (1);
	if (load_tex(data, &data->tex[2], data->config.we_tex))
		return (1);
	if (load_tex(data, &data->tex[3], data->config.ea_tex))
		return (1);
	return (0);
}
