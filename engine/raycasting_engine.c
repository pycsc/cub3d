/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    raycasting_engine.c                                   +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 16:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 22:30:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_wall_stripe(t_data *data, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < 600)
	{
		if (y < start)
			my_mlx_pixel_put(&data->img, x, y, data->config.ceiling_col);
		else if (y > end)
			my_mlx_pixel_put(&data->img, x, y, data->config.floor_col);
		else
			my_mlx_pixel_put(&data->img, x, y, 0x00FF0000);
		y++;
	}
}

static void	init_dda(t_data *data, double rx, double ry, double *sd)
{
	double	ddx;
	double	ddy;

	ddx = fabs(1 / rx);
	ddy = fabs(1 / ry);
	if (rx < 0)
		sd[0] = (data->player.x - (int)data->player.x) * ddx;
	else
		sd[0] = ((int)data->player.x + 1.0 - data->player.x) * ddx;
	if (ry < 0)
		sd[1] = (data->player.y - (int)data->player.y) * ddy;
	else
		sd[1] = ((int)data->player.y + 1.0 - data->player.y) * ddy;
}

static void	perform_dda(t_data *data, double rx, double ry, int x)
{
	double	sd[2];
	double	dd[2];
	double	pwd;
	int		map[2];
	int		step[2];
	int		side;
	int		lh;

	dd[0] = fabs(1 / rx);
	dd[1] = fabs(1 / ry);
	init_dda(data, rx, ry, sd);
	map[0] = (int)data->player.x;
	map[1] = (int)data->player.y;
	step[0] = (rx < 0) ? -1 : 1;
	step[1] = (ry < 0) ? -1 : 1;
	while (data->map[map[1]][map[0]] != '1')
	{
		if (sd[0] < sd[1] && (side = 0))
			(1) && (sd[0] += dd[0]) && (map[0] += step[0]);
		else if ((side = 1))
			(1) && (sd[1] += dd[1]) && (map[1] += step[1]);
	}
	pwd = (side == 0) ? (sd[0] - dd[0]) : (sd[1] - dd[1]);
	lh = (int)(600 / pwd);
	draw_wall_stripe(data, x, fmax(0, -lh / 2 + 300), fmin(599, lh / 2 + 300));
}

void	render_frame(t_data *data)
{
	int		x;
	double	cx;
	double	rx;
	double	ry;

	x = 0;
	while (x < 800)
	{
		cx = 2 * x / (double)800 - 1;
		rx = data->player.dir_x + data->player.plane_x * cx;
		ry = data->player.dir_y + data->player.plane_y * cx;
		perform_dda(data, rx, ry, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
