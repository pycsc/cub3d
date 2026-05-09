/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    line_renderer.c                                       +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 15:45:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:45:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_coin_pixel(t_data *data, int x, int y, t_dda *d)
{
	double	clh;
	double	dy;
	double	dx;
	double	rot;

	clh = 600 / d->coin_pwd;
	dy = (y - 300.0) / (clh / 2.0);
	dx = (d->coin_wall_x - 0.5) * 2.0;
	rot = sin(data->frame * 0.1) * 0.8;
	if (dx * dx / (rot * rot + 0.001) + dy * dy < 0.15)
		my_mlx_pixel_put(&data->img, x, y, 0x00FFD700);
}

static void	draw_wall_pixel(t_data *data, int x, int y, t_dda *d)
{
	int		tn;
	double	wx;
	int		tx;
	int		lh;
	double	tp;

	tn = (d->side == 0) ? ((d->rx > 0) ? 3 : 2) : ((d->ry > 0) ? 1 : 0);
	wx = (d->side == 0) ? data->player.y + d->pwd * d->ry : \
						data->player.x + d->pwd * d->rx;
	wx -= floor(wx);
	tx = (int)(wx * (double)data->tex[tn].width);
	if ((d->side == 0 && d->rx > 0) || (d->side == 1 && d->ry < 0))
		tx = data->tex[tn].width - tx - 1;
	lh = (int)(600 / d->pwd);
	tp = (y - 300 + lh / 2.0) * (1.0 * data->tex[tn].height / lh);
	char *dst = data->tex[tn].addr + ((int)tp * data->tex[tn].line_length + \
				tx * (data->tex[tn].bits_per_pixel / 8));
	my_mlx_pixel_put(&data->img, x, y, *(unsigned int *)dst);
}

void	draw_line_textured(t_data *data, int x, t_dda *d)
{
	int		lh;
	int		start;
	int		end;
	int		y;

	lh = (int)(600 / d->pwd);
	start = fmax(0, -lh / 2 + 300);
	end = fmin(599, lh / 2 + 300);
	y = -1;
	while (++y < 600)
	{
		if (y < start)
			my_mlx_pixel_put(&data->img, x, y, data->config.ceiling_col);
		else if (y > end)
			my_mlx_pixel_put(&data->img, x, y, data->config.floor_col);
		else
			draw_wall_pixel(data, x, y, d);
		if (d->hit_coin)
			draw_coin_pixel(data, x, y, d);
	}
}
