/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    parser_utils.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 19:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 19:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * is_config_line - Checks if a line is a configuration element (NO, SO, etc.).
 * @line: The line to check.
 *
 * Return: 1 if it is a configuration line, 0 otherwise.
 */
int	is_config_line(char *line)
{
	if (!line || *line == '\n')
		return (0);
	if (!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3) ||
		!strncmp(line, "WE ", 3) || !strncmp(line, "EA ", 3) ||
		!strncmp(line, "F ", 2) || !strncmp(line, "C ", 2))
		return (1);
	return (0);
}

/**
 * parse_line - Parses a single configuration line.
 * @line: The line to parse.
 * @data: Pointer to the main project structure.
 *
 * Return: 0 on success, 1 on error.
 */
int	parse_line(char *line, t_data *data)
{
	(void)line;
	(void)data;
	return (0);
}
