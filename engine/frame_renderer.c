/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    frame_renderer.c                                      +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 15:45:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:45:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	apply_dot_filter(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			if (x % 3 == 2 || y % 3 == 2)
				my_mlx_pixel_put(&data->img, x, y, 0);
			x++;
		}
		y++;
	}
}

void	render_frame(t_data *data)
{
	int		x;
	double	cx;

	x = 0;
	data->frame++;
	while (x < 800)
	{
		cx = 2 * x / (double)800 - 1;
		perform_dda(data, data->player.dir_x + data->player.plane_x * cx, \
			data->player.dir_y + data->player.plane_y * cx, x);
		x++;
	}
	apply_dot_filter(data);
	draw_minimap(data);
	draw_hud(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
