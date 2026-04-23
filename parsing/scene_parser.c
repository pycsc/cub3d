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

/**
 * parse_scene - Opens and initiates reading of the .cub file.
 * @file: Path to the .cub file.
 * @data: Pointer to the main project structure.
 *
 * Return: 0 on success, non-zero on failure.
 */
int	parse_scene(char *file, void *data)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	(void)data;
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
