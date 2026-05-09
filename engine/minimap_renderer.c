/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    minimap_renderer.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 07:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 14:45:00 by lucas                 #+                */
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

static void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
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

	scale = 10;
	get_map_dimensions(data->map, &map_w, &map_h);
	off[0] = 790 - (map_w * scale);
	off[1] = 590 - (map_h * scale);
	// Background
	draw_rect(data, off[0] - 5, off[1] - 5, (map_w * scale) + 10, (map_h * scale) + 10, 0x11000000);
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
			{
				// Color match: horizontal walls Orange, vertical Cyan
				if (y % 2 == 0)
					draw_square(data, off[0] + x * scale, off[1] + y * scale, scale - 1, 0xFF8800);
				else
					draw_square(data, off[0] + x * scale, off[1] + y * scale, scale - 1, 0x4ECBD4);
			}
			else if (data->map[y][x] != ' ' && data->map[y][x] != '\0')
				draw_square(data, off[0] + x * scale, off[1] + y * scale, scale - 1, 0x333333);
		}
	}
	// Player
	draw_square(data, off[0] + data->player.x * scale - 2, \
		off[1] + data->player.y * scale - 2, 4, 0xFFFFFF);
	// Direction
	draw_square(data, off[0] + (data->player.x + data->player.dir_x * 0.8) * scale - 1, \
		off[1] + (data->player.y + data->player.dir_y * 0.8) * scale - 1, 3, 0xFF0000);
}
