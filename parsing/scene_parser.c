/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    scene_parser.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 17:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 06:47:10 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <errno.h>

static int	is_config_full(t_config *config)
{
	return (config->no_tex && config->so_tex && config->we_tex && \
			config->ea_tex && config->floor_col != -1 && \
			config->ceiling_col != -1);
}

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	return (line[i] == '\0' || line[i] == '\n');
}

static int	process_line(char *line, t_data *data)
{
	if (is_empty_line(line))
	{
		if (data->map_list)
			return (print_error("Empty line inside map"), 1);
		return (0);
	}
	if (!is_config_full(&data->config))
	{
		if (is_config_line(line))
			return (parse_line(line, data));
		if (is_map_line(line))
			return (print_error("Map before configuration"), 1);
		return (print_error("Invalid configuration line"), 1);
	}
	if (is_map_line(line))
		return (add_map_line(line, data));
	return (print_error("Invalid line after configuration"), 1);
}

int	parse_scene(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	ft_memset(data, 0, sizeof(t_data));
	data->config.floor_col = -1;
	data->config.ceiling_col = -1;
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(line, data))
			return (free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!is_config_full(&data->config) || !data->map_list)
		return (print_error("Incomplete configuration or missing map"), 1);
	if (lst_to_array(data))
		return (print_error("Memory allocation failed"), 1);
	return (validate_map(data));
}
