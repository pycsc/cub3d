/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    minimap_renderer.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 07:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:45:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

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
	draw_rect(data, off[0] - 2, off[1] - 2, (map_w * scale) + 4, \
		(map_h * scale) + 4, 0x000000);
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
				draw_rect(data, off[0] + x * scale, off[1] + y * scale, \
					scale - 1, scale - 1, 0x444444);
			else if (data->map[y][x] == '2')
				draw_rect(data, off[0] + x * scale + 2, off[1] + y * scale + 2, \
					3, 3, 0xFFD700);
			else if (data->map[y][x] != ' ' && data->map[y][x] != '\0')
				draw_rect(data, off[0] + x * scale, off[1] + y * scale, \
					scale - 1, scale - 1, 0x111111);
		}
	}
	draw_rect(data, off[0] + (int)data->player.x * scale - 1, \
		off[1] + (int)data->player.y * scale - 1, 3, 3, 0xFFFFFF);
	draw_rect(data, off[0] + (data->player.x + data->player.dir_x * 0.5) * \
		scale - 1, off[1] + (data->player.y + data->player.dir_y * 0.5) * \
		scale - 1, 2, 2, 0xFF0000);
}
