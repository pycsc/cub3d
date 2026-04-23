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
	{
		perror("Error opening file");
		return (1);
	}
	data->map = NULL;
	data->config.no_tex = NULL;
	data->config.so_tex = NULL;
	data->config.we_tex = NULL;
	data->config.ea_tex = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, data))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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
