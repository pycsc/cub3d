/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    minimap_renderer.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 07:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 06:47:10 by lucas                 #+                */
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

static unsigned int	get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
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

static void	draw_logo(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < data->logo.height)
	{
		x = 0;
		while (x < data->logo.width)
		{
			color = get_tex_color(&data->logo, x, y);
			if (color != 0xFF000000)
				my_mlx_pixel_put(&data->img, 760 + x, 560 + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	int	scale;

	scale = 10;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			map_x = 10 + x * scale;
			map_y = 10 + y * scale;
			if (data->map[y][x] == '1')
				draw_square(data, map_x, map_y, scale - 1, 0x00FFFFFF);
			else if (data->map[y][x] != ' ' && data->map[y][x] != '\0')
				draw_square(data, map_x, map_y, scale - 1, 0x00888888);
			x++;
		}
		y++;
	}
	draw_square(data, 10 + data->player.x * scale - 2, \
		10 + data->player.y * scale - 2, 4, 0x00FF0000);
	draw_logo(data);
}
