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

static int	set_tex(char **tex, char *line)
{
	if (*tex)
		return (1);
	*tex = ft_strdup(line + 3);
	if (!(*tex))
		return (1);
	return (0);
}

static int	set_color(int *col, char *line)
{
	(void)col;
	(void)line;
	return (0);
}

int	parse_line(char *line, t_data *data)
{
	if (!strncmp(line, "NO ", 3))
		return (set_tex(&data->config.no_tex, line));
	if (!strncmp(line, "SO ", 3))
		return (set_tex(&data->config.so_tex, line));
	if (!strncmp(line, "WE ", 3))
		return (set_tex(&data->config.we_tex, line));
	if (!strncmp(line, "EA ", 3))
		return (set_tex(&data->config.ea_tex, line));
	if (!strncmp(line, "F ", 2))
		return (set_color(&data->config.floor_col, line));
	if (!strncmp(line, "C ", 2))
		return (set_color(&data->config.ceiling_col, line));
	return (0);
}
