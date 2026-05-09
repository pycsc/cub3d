/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    map_parser.c                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 21:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:46:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	if (!line || *line == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && \
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && \
			line[i] != 'W' && line[i] != '2')
			return (0);
		i++;
	}
	return (1);
}

int	add_map_line(char *line, t_data *data)
{
	t_list	*new;
	char	*content;

	content = ft_strdup(line);
	if (!content)
		return (1);
	if (content[ft_strlen(content) - 1] == '\n')
		content[ft_strlen(content) - 1] = '\0';
	new = ft_lstnew(content);
	if (!new)
		return (free(content), 1);
	ft_lstadd_back(&data->map_list, new);
	return (0);
}

static int	check_cell(char **map, int y, int x)
{
	if (y == 0 || !map[y + 1] || x == 0 || (int)ft_strlen(map[y]) <= x + 1)
		return (0);
	if (ft_strlen(map[y - 1]) <= (size_t)x || map[y - 1][x] == ' ' || \
		map[y - 1][x] == '\0')
		return (0);
	if (ft_strlen(map[y + 1]) <= (size_t)x || map[y + 1][x] == ' ' || \
		map[y + 1][x] == '\0')
		return (0);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || \
		map[y][x + 1] == '\0')
		return (0);
	return (1);
}

int	validate_map(t_data *data)
{
	int	x;
	int	y;
	int	player;

	player = 0;
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				if (++player > 1 || !check_cell(data->map, y, x))
					return (print_error("Invalid player position or count"), 1);
			}
			else if (data->map[y][x] == '0' || data->map[y][x] == '2')
			{
				if (!check_cell(data->map, y, x))
					return (print_error("Map is not closed/surrounded by walls"), 1);
			}
		}
	}
	return ((player != 1) ? (print_error("Exactly one player required"), 1) : 0);
}

int	lst_to_array(t_data *data)
{
	int		size;
	int		i;
	t_list	*tmp;

	size = ft_lstsize(data->map_list);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
		return (1);
	tmp = data->map_list;
	i = 0;
	while (tmp)
	{
		data->map[i++] = (char *)tmp->content;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
	return (0);
}
