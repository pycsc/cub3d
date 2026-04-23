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

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;

	(void)argc;
	(void)argv;
	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 800, 600, "cub3D");
	if (!win)
		return (1);
	mlx_loop(mlx);
	return (0);
}
