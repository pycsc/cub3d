/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    map_parser.c                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 21:00:00 by lucas                  ##+              */
/*    Updated: 2026/04/23 21:00:00 by lucas                 #+                */
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
			line[i] != 'W')
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
	{
		free(content);
		return (1);
	}
	ft_lstadd_back(&data->map_list, new);
	return (0);
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

static void	set_dir(t_data *data, char dir)
{
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	if (dir == 'N')
		(1) && (data->player.dir_y = -1) && (data->player.plane_x = 0.66);
	if (dir == 'S')
		(1) && (data->player.dir_y = 1) && (data->player.plane_x = -0.66);
	if (dir == 'E')
		(1) && (data->player.dir_x = 1) && (data->player.plane_y = 0.66);
	if (dir == 'W')
		(1) && (data->player.dir_x = -1) && (data->player.plane_y = -0.66);
}

int	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				set_dir(data, data->map[y][x]);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
