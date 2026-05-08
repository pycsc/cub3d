/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    player_controller.c                                   +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 23:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 06:47:10 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, double dx, double dy)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	new_x = data->player.x + dx * move_speed;
	new_y = data->player.y + dy * move_speed;
	if (data->map[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
	if (data->map[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = angle * 0.03;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rot_speed) - \
						data->player.dir_y * sin(rot_speed);
	data->player.dir_y = old_dir_x * sin(rot_speed) + \
						data->player.dir_y * cos(rot_speed);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rot_speed) - \
						data->player.plane_y * sin(rot_speed);
	data->player.plane_y = old_plane_x * sin(rot_speed) + \
						data->player.plane_y * cos(rot_speed);
}
