/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    player_controller.c                                   +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 23:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:15:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawn_coin(t_data *data)
{
	int	x;
	int	y;
	int	map_w;
	int	map_h;

	map_h = 0;
	while (data->map[map_h])
		map_h++;
	while (1)
	{
		y = rand() % map_h;
		map_w = ft_strlen(data->map[y]);
		if (map_w == 0)
			continue ;
		x = rand() % map_w;
		if (data->map[y][x] == '0')
		{
			data->map[y][x] = '2';
			break ;
		}
	}
}

void	move_player(t_data *data, double dx, double dy)
{
	double	ms;
	double	nx;
	double	ny;

	ms = 0.05;
	nx = data->player.x + dx * ms;
	ny = data->player.y + dy * ms;
	if (data->map[(int)data->player.y][(int)nx] != '1')
		data->player.x = nx;
	if (data->map[(int)ny][(int)data->player.x] != '1')
		data->player.y = ny;
	if (data->map[(int)data->player.y][(int)data->player.x] == '2')
	{
		data->map[(int)data->player.y][(int)data->player.x] = '0';
		data->score += 100;
		spawn_coin(data);
	}
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rs = angle * 0.03;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rs) - \
						data->player.dir_y * sin(rs);
	data->player.dir_y = old_dir_x * sin(rs) + \
						data->player.dir_y * cos(rs);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rs) - \
						data->player.plane_y * sin(rs);
	data->player.plane_y = old_plane_x * sin(rs) + \
						data->player.plane_y * cos(rs);
}
