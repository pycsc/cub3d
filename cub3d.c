/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    cub3d.c                                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 15:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 16:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <time.h>

int	close_window(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode >= 0 && keycode < 65536)
		data->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 65536)
		data->keys[keycode] = 0;
	return (0);
}

int	update_game(t_data *data)
{
	if (data->keys[KEY_W])
		move_player(data, data->player.dir_x, data->player.dir_y);
	if (data->keys[KEY_S])
		move_player(data, -data->player.dir_x, -data->player.dir_y);
	if (data->keys[KEY_A])
		move_player(data, -data->player.plane_x, -data->player.plane_y);
	if (data->keys[KEY_D])
		move_player(data, data->player.plane_x, data->player.plane_y);
	if (data->keys[KEY_LEFT])
		rotate_player(data, -1);
	if (data->keys[KEY_RIGHT])
		rotate_player(data, 1);
	render_frame(data);
	return (0);
}

static int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (print_error("Failed to initialize MiniLibX"), 1);
	data->win = mlx_new_window(data->mlx, 800, 600, "cub3D");
	if (!data->win)
		return (print_error("Failed to create window"), 1);
	if (load_textures(data))
		return (1);
	data->img.img = mlx_new_image(data->mlx, 800, 600);
	if (!data->img.img)
		return (print_error("Failed to create main image"), 1);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, \
		&data->img.line_length, &data->img.endian);
	set_platform_icon(data, "assets/logo.png");
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2), 1);
	srand(time(NULL));
	ft_memset(&data, 0, sizeof(t_data));
	if (parse_scene(argv[1], &data))
		return (1);
	if (init_player(&data))
		return (1);
	data.health = 100;
	data.ammo = 100;
	spawn_coin(&data);
	if (init_mlx(&data))
		return (1);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, update_game, &data);
	mlx_loop(data.mlx);
	return (0);
}
