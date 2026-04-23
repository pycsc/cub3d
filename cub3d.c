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

static void	print_data(t_data *data)
{
	int	i;

	printf("NO: %s\n", data->config.no_tex);
	printf("SO: %s\n", data->config.so_tex);
	printf("WE: %s\n", data->config.we_tex);
	printf("EA: %s\n", data->config.ea_tex);
	printf("Floor: %d\n", data->config.floor_col);
	printf("Ceiling: %d\n", data->config.ceiling_col);
	if (data->map)
	{
		i = 0;
		while (data->map[i])
			printf("%s\n", data->map[i++]);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (1);
	if (parse_scene(argv[1], &data))
		return (1);
	print_data(&data);
	return (0);
}
