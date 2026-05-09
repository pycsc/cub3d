/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    player_parser.c                                       +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 15:46:19 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:46:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_data *data, char dir)
{
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	if (dir == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	if (dir == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	if (dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
	if (dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
}

int	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				set_dir(data, data->map[y][x]);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
