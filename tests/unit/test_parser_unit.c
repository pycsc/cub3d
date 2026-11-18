/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_parser_unit.c                                     +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                    +########+            */
/*                                                          +###+             */
/*    Created: 2026/11/18 16:51:00 by lucas                  ##+              */
/*    Updated: 2026/11/18 16:51:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>

static void	test_line_classifiers(void)
{
	t_data	data;

	assert(is_config_line("NO ./textures/north.xpm\n") == 1);
	assert(is_config_line("F 220,100,0\n") == 1);
	assert(is_config_line("111111\n") == 0);
	assert(is_map_line("1110011\n") == 1);
	assert(is_map_line("100N001\n") == 1);
	assert(is_map_line("INVALID\n") == 0);
	ft_memset(&data, 0, sizeof(t_data));
	data.config.floor_col = -1;
	data.config.ceiling_col = -1;
	assert(parse_line("F 220,100,0\n", &data) == 0);
	assert(data.config.floor_col == ((220 << 16) | (100 << 8) | 0));
}

int	main(void)
{
	test_line_classifiers();
	printf("unit: OK\n");
	return (0);
}
