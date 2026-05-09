/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    minimap_renderer.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 07:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_rect(t_data *data, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			my_mlx_pixel_put(&data->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	get_map_dimensions(char **map, int *width, int *height)
{
	int	y;
	int	x;
	int	max_x;

	y = 0;
	max_x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > max_x)
			max_x = x;
		y++;
	}
	*width = max_x;
	*height = y;
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	map_w;
	int	map_h;
	int	scale;
	int	off[2];

	scale = 8;
	get_map_dimensions(data->map, &map_w, &map_h);
	off[0] = 790 - (map_w * scale);
	off[1] = 590 - (map_h * scale);
	draw_rect(data, off[0] - 2, off[1] - 2, (map_w * scale) + 4, (map_h * scale) + 4, 0x000000);
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
			{
				if (y == 0) // North wall (Top) -> Cyan
					draw_rect(data, off[0] + x * scale, off[1] + y * scale, scale - 1, scale - 1, 0x4ECBD4);
				else if (!data->map[y + 1]) // South wall (Bottom) -> Orange
					draw_rect(data, off[0] + x * scale, off[1] + y * scale, scale - 1, scale - 1, 0xFF8800);
				else // West/East or inner walls -> Gray
					draw_rect(data, off[0] + x * scale, off[1] + y * scale, scale - 1, scale - 1, 0x444444);
			}
			else if (data->map[y][x] != ' ' && data->map[y][x] != '\0')
				draw_rect(data, off[0] + x * scale, off[1] + y * scale, scale - 1, scale - 1, 0x111111);
		}
	}
	draw_rect(data, off[0] + data->player.x * scale - 1, off[1] + data->player.y * scale - 1, 3, 3, 0xFFFFFF);
	draw_rect(data, off[0] + (data->player.x + data->player.dir_x * 0.5) * scale - 1, \
		off[1] + (data->player.y + data->player.dir_y * 0.5) * scale - 1, 2, 2, 0xFF0000);
}
