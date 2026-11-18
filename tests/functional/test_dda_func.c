/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_dda_func.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                    +########+            */
/*                                                          +###+             */
/*    Created: 2026/11/18 16:51:15 by lucas                  ##+              */
/*    Updated: 2026/11/18 16:51:15 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>

static void	test_map_validation_and_player(void)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	assert(add_map_line("1111\n", &data) == 0);
	assert(add_map_line("10N1\n", &data) == 0);
	assert(add_map_line("1111\n", &data) == 0);
	assert(lst_to_array(&data) == 0);
	assert(validate_map(&data) == 0);
	assert(init_player(&data) == 0);
	assert(data.player.x > 1.0 && data.player.y > 1.0);
	rotate_player(&data, 0.5);
	move_player(&data, 0.1, 0.0);
	free(data.map);
	ft_lstclear(&data.map_list, free);
}

int	main(void)
{
	test_map_validation_and_player();
	printf("functional: OK\n");
	return (0);
}
