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

static unsigned int	get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static void	draw_line_textured(t_data *data, int x, int side, double pwd, double rx, double ry, int lh, int is_coin)
{
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		y;
	double	step;
	double	tex_pos;
	int		start;
	int		end;

	if (side == 0)
		tex_num = (rx > 0) ? 3 : 2;
	else
		tex_num = (ry > 0) ? 1 : 0;
	if (side == 0)
		wall_x = data->player.y + pwd * ry;
	else
		wall_x = data->player.x + pwd * rx;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->tex[tex_num].width);
	if ((side == 0 && rx > 0) || (side == 1 && ry < 0))
		tex_x = data->tex[tex_num].width - tex_x - 1;
	step = 1.0 * data->tex[tex_num].height / lh;
	start = fmax(0, -lh / 2 + 300);
	end = fmin(599, lh / 2 + 300);
	if (is_coin)
	{
		start = fmax(0, -lh / 4 + 300);
		end = fmin(599, lh / 4 + 300);
	}
	tex_pos = (start - 300 + lh / 2.0) * step;
	y = -1;
	while (++y < 600)
	{
		if (y < start)
			my_mlx_pixel_put(&data->img, x, y, data->config.ceiling_col);
		else if (y > end)
			my_mlx_pixel_put(&data->img, x, y, data->config.floor_col);
		else
		{
			if (is_coin)
			{
				double hit_dist = fabs(wall_x - 0.5);
				if (hit_dist < 0.3)
					my_mlx_pixel_put(&data->img, x, y, 0x00FFD700);
				else
				{
					if (y < -lh / 2 + 300)
						my_mlx_pixel_put(&data->img, x, y, data->config.ceiling_col);
					else
						my_mlx_pixel_put(&data->img, x, y, data->config.floor_col);
				}
			}
			else
				my_mlx_pixel_put(&data->img, x, y, get_tex_color(&data->tex[tex_num], tex_x, (int)tex_pos));
			tex_pos += step;
		}
	}
}

static void	perform_dda(t_data *data, double rx, double ry, int x)
{
	double	sd[2];
	double	dd[2];
	int		map[2];
	int		step[2];
	int		side = 0;
	int		is_coin = 0;

	dd[0] = fabs(1 / rx);
	dd[1] = fabs(1 / ry);
	map[0] = (int)data->player.x;
	map[1] = (int)data->player.y;
	step[0] = (rx < 0) ? -1 : 1;
	step[1] = (ry < 0) ? -1 : 1;
	sd[0] = (rx < 0) ? (data->player.x - map[0]) * dd[0] : (map[0] + 1.0 - data->player.x) * dd[0];
	sd[1] = (ry < 0) ? (data->player.y - map[1]) * dd[1] : (map[1] + 1.0 - data->player.y) * dd[1];
	while (data->map[map[1]][map[0]] != '1')
	{
		if (data->map[map[1]][map[0]] == '2')
		{
			is_coin = 1;
			break ;
		}
		if (sd[0] < sd[1])
		{
			sd[0] += dd[0];
			map[0] += step[0];
			side = 0;
		}
		else
		{
			sd[1] += dd[1];
			map[1] += step[1];
			side = 1;
		}
	}
	double pwd;
	if (side == 0)
		pwd = (map[0] - data->player.x + (1 - step[0]) / 2) / rx;
	else
		pwd = (map[1] - data->player.y + (1 - step[1]) / 2) / ry;
	draw_line_textured(data, x, side, pwd, rx, ry, (int)(600 / pwd), is_coin);
}

static void	apply_dot_filter(t_data *data)
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
