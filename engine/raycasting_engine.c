/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    raycasting_engine.c                                   +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 16:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 16:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			if (y < 300)
				my_mlx_pixel_put(&data->img, x, y, data->config.ceiling_col);
			else
				my_mlx_pixel_put(&data->img, x, y, data->config.floor_col);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

/**
 * update_player_view - Placeholder to update view orientation.
 * @data: Pointer to the main project structure.
 */
void	update_player_view(void *data)
{
	(void)data;
}

/**
 * calculate_wall_height - Placeholder to calculate wall projection height.
 * @dist: Distance to the wall.
 *
 * Return: Calculated height of the wall.
 */
double	calculate_wall_height(double dist)
{
	(void)dist;
	return (0.0);
}
