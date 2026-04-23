/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    cub3d.c                                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 15:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 15:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	close_window(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		close_window(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (1);
	if (parse_scene(argv[1], &data))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 800, 600, "cub3D");
	if (!data.win)
		return (1);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
