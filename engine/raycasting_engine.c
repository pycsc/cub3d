/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    raycasting_engine.c                                   +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 16:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:30:00 by lucas                 #+                */
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

static void	draw_wall_pixel(t_data *data, int x, int y, t_dda *d)
{
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		lh;

	if (d->side == 0)
		tex_num = (d->rx > 0) ? 3 : 2;
	else
		tex_num = (d->ry > 0) ? 1 : 0;
	if (d->side == 0)
		wall_x = data->player.y + d->pwd * d->ry;
	else
		wall_x = data->player.x + d->pwd * d->rx;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->tex[tex_num].width);
	if ((d->side == 0 && d->rx > 0) || (d->side == 1 && d->ry < 0))
		tex_x = data->tex[tex_num].width - tex_x - 1;
	lh = (int)(600 / d->pwd);
	step = 1.0 * data->tex[tex_num].height / lh;
	tex_pos = (y - 300 + lh / 2.0) * step;
	char *dst = data->tex[tex_num].addr + ((int)tex_pos * data->tex[tex_num].line_length + tex_x * (data->tex[tex_num].bits_per_pixel / 8));
	my_mlx_pixel_put(&data->img, x, y, *(unsigned int *)dst);
}

static void	draw_line_textured(t_data *data, int x, t_dda *d)
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
		{
			double clh = 600 / d->coin_pwd;
			double dy = (y - 300.0) / (clh / 2.0);
			double dx = (d->coin_wall_x - 0.5) * 2.0;
			double rot = sin(data->frame * 0.1) * 0.8;
			if (dx * dx / (rot * rot + 0.01) + dy * dy < 0.2)
				my_mlx_pixel_put(&data->img, x, y, 0x00FFD700);
		}
	}
}

static void	perform_dda(t_data *data, double rx, double ry, int x)
{
	t_dda	d;

	ft_memset(&d, 0, sizeof(t_dda));
	d.rx = rx; d.ry = ry;
	d.dd[0] = fabs(1 / rx); d.dd[1] = fabs(1 / ry);
	d.map[0] = (int)data->player.x; d.map[1] = (int)data->player.y;
	d.step[0] = (rx < 0) ? -1 : 1; d.step[1] = (ry < 0) ? -1 : 1;
	d.sd[0] = (rx < 0) ? (data->player.x - d.map[0]) * d.dd[0] : (d.map[0] + 1.0 - data->player.x) * d.dd[0];
	d.sd[1] = (ry < 0) ? (data->player.y - d.map[1]) * d.dd[1] : (d.map[1] + 1.0 - data->player.y) * d.dd[1];
	while (data->map[d.map[1]][d.map[0]] != '1')
	{
		if (!d.hit_coin && data->map[d.map[1]][d.map[0]] == '2')
		{
			d.hit_coin = 1;
			d.coin_pwd = (d.side == 0) ? (d.map[0] - data->player.x + (1 - d.step[0]) / 2) / rx : (d.map[1] - data->player.y + (1 - d.step[1]) / 2) / ry;
			d.coin_wall_x = (d.side == 0) ? data->player.y + d.coin_pwd * ry : data->player.x + d.coin_pwd * rx;
			d.coin_wall_x -= floor(d.coin_wall_x);
		}
		if (d.sd[0] < d.sd[1] && (d.side = 0)) d.sd[0] += d.dd[0], d.map[0] += d.step[0];
		else if ((d.side = 1)) d.sd[1] += d.dd[1], d.map[1] += d.step[1];
	}
	d.pwd = (d.side == 0) ? (d.map[0] - data->player.x + (1 - d.step[0]) / 2) / rx : (d.map[1] - data->player.y + (1 - d.step[1]) / 2) / ry;
	draw_line_textured(data, x, &d);
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
