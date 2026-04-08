/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    cub3d.c                                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/08 06:25:19 by lucas                  ##+              */
/*    Updated: 2026/04/08 06:25:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

/* Main program for cub3D ray-casting FPS game */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (parse_scene(argv[1], &data) == -1)
		return (1);
	if (init_mlx_win(&data) == -1)
		return (cleanup(&data, 1));
	if (start_rendering(&data) == -1)
		return (cleanup(&data, 1));
	return (cleanup(&data, 0));
}
