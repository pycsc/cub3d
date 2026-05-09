/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    minimap_renderer.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 07:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 14:15:00 by lucas                 #+                */
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
	int	offset_x;
	int	offset_y;

	scale = 10;
	get_map_dimensions(data->map, &map_w, &map_h);
	offset_x = 790 - (map_w * scale);
	offset_y = 590 - (map_h * scale);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_square(data, offset_x + x * scale, offset_y + y * scale, scale - 1, 0x00FFFFFF);
			else if (data->map[y][x] != ' ' && data->map[y][x] != '\0')
				draw_square(data, offset_x + x * scale, offset_y + y * scale, scale - 1, 0x00888888);
			x++;
		}
		y++;
	}
	draw_square(data, offset_x + data->player.x * scale - 2, \
		offset_y + data->player.y * scale - 2, 4, 0x00FF0000);
}
