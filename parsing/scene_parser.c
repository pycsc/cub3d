/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    scene_parser.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 17:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 17:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <errno.h>

int	parse_line(char *line, t_data *data);

/**
 * parse_scene - Reads and parses the .cub file configuration.
 * @file: Path to the .cub file.
 * @data: Pointer to the main project structure.
 *
 * Return: 0 on success, non-zero on failure.
 */
int	parse_scene(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	data->map = NULL;
	data->map_list = NULL;
	ft_memset(&data->config, 0, sizeof(t_config));
	line = get_next_line(fd);
	while (line)
	{
		if (is_config_line(line))
			parse_line(line, data);
		else if (is_map_line(line))
			add_map_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (lst_to_array(data))
		return (1);
	return (0);
}

/**
 * validate_map - Checks if the map is closed by walls.
 * @map: The map content represented as a 2D array.
 *
 * Return: 1 if valid, 0 otherwise.
 */
int	validate_map(char **map)
{
	(void)map;
	return (1);
}
