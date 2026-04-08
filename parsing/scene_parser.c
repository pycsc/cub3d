/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    scene_parser.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/08 06:25:19 by lucas                  ##+              */
/*    Updated: 2026/04/08 06:25:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

/* Scene parser for .cub files */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static void	init_data(t_data *data)
{
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->pos_x = 0.0;
	data->pos_y = 0.0;
	data->dir_x = 0.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.0;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
}

int	open_scene_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nScene file not found: %s\n", path);
		return (-1);
	}
	return (fd);
}

int	parse_scene(char *path, t_data *data)
{
	char	*line;
	int		fd;
	int		line_num;
	int		map_started;

	if (!path)
		return (ft_printf("Error\nNo scene path provided\n"), 1);
	init_data(data);
	fd = open_scene_file(path);
	if (fd < 0)
		return (1);
	line_num = 1;
	map_started = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!map_started)
		{
			if (process_non_map_line(line, data) == -1)
			{
				free(line);
				close(fd);
				return (1);
			}
			if (line[0] && ft_strchr("1234567890", line[0]))
				map_started = 1;
		}
		else if (process_map_line(line, data) == -1)
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line_num++;
	}
	if (check_map_validity(data) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	process_non_map_line(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line + 3, "north", data));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line + 3, "south", data));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line + 3, "west", data));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line + 3, "east", data));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line + 2, "floor", data));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line + 2, "ceiling", data));
	else if (line[0] == '\0' || ft_strchr(" \t", line[0]))
		return (0);
	else
		return (ft_printf("Error\nInvalid config line: %s\n", line), -1);
}

int	parse_texture(char *path, char *type, t_data *data)
{
	void	*texture;

	if (type && ft_strncmp(type, "north", 5) == 0)
	{
		texture = mlx_xpm_file_to_image(data->mlx, path, &data->img_width, &data->img_height);
		if (!texture)
			return (ft_printf("Error\nFailed to load north texture\n"), -1);
		data->north_texture = texture;
	}
	else if (type && ft_strncmp(type, "south", 5) == 0)
	{
		texture = mlx_xpm_file_to_image(data->mlx, path, &data->img_width, &data->img_height);
		if (!texture)
			return (ft_printf("Error\nFailed to load south texture\n"), -1);
		data->south_texture = texture;
	}
	else if (type && ft_strncmp(type, "west", 4) == 0)
	{
		texture = mlx_xpm_file_to_image(data->mlx, path, &data->img_width, &data->img_height);
		if (!texture)
			return (ft_printf("Error\nFailed to load west texture\n"), -1);
		data->west_texture = texture;
	}
	else if (type && ft_strncmp(type, "east", 4) == 0)
	{
		texture = mlx_xpm_file_to_image(data->mlx, path, &data->img_width, &data->img_height);
		if (!texture)
			return (ft_printf("Error\nFailed to load east texture\n"), -1);
		data->east_texture = texture;
	}
	return (0);
}

int	parse_color(char *str, char *type, t_data *data)
{
	int	r;
	int	g;
	int	b;
	char **parts;

	if (type && ft_strncmp(type, "floor", 5) == 0)
	{
		parts = ft_split(str, ',');
		if (parts && parts[0] && parts[1] && parts[2])
		{
			r = ft_atoi(parts[0]) & 255;
			g = ft_atoi(parts[1]) & 255;
			b = ft_atoi(parts[2]) & 255;
			data->floor_color = (r << 16) | (g << 8) | b;
			free_array(parts);
		}
		return (parts ? (0) : (-1));
	}
	else if (type && ft_strncmp(type, "ceiling", 7) == 0)
	{
		parts = ft_split(str, ',');
		if (parts && parts[0] && parts[1] && parts[2])
		{
			r = ft_atoi(parts[0]) & 255;
			g = ft_atoi(parts[1]) & 255;
			b = ft_atoi(parts[2]) & 255;
			data->ceiling_color = (r << 16) | (g << 8) | b;
			free_array(parts);
		}
		return (parts ? (0) : (-1));
	}
	return (-1);
}

int	process_map_line(char *line, t_data *data)
{
	char	**map_part;
	int		i;

	map_part = ft_split(line, ' ');
	if (!map_part)
		return (-1);
	data->map = ft_realloc(data->map, &(data->map_height), data->map_width, map_part[0]);
	if (!data->map[data->map_height - 1])
	{
		free_array(map_part);
		return (-1);
	}
	for (i = 1; map_part[i]; i++)
	{
		data->map[data->map_height - 1] = ft_realloc(data->map[data->map_height - 1],
			&(data->map_width), 0, map_part[i]);
		if (!data->map[data->map_height - 1])
		{
			free_array(map_part);
			return (-1);
		}
	}
	free_array(map_part);
	return (0);
}

int	check_map_validity(t_data *data)
{
	int	x;
	int	y;

	if (!data->map || data->map_height == 0 || data->map_width == 0)
		return (ft_printf("Error\nInvalid map data\n"), -1);
	for (y = 0; y < data->map_height; y++)
	{
		if (!data->map[y])
			return (ft_printf("Error\nInvalid map row\n"), -1);
		for (x = 0; x < data->map_width; x++)
		{
			if (!data->map[y][x])
				return (ft_printf("Error\nInvalid map cell\n"), -1);
			if (ft_strchr("NSWE", data->map[y][x])
				&& ft_strcmp(data->map[y][x], "N") != 0) 
				return (ft_printf("Error\nMultiple start positions\n"), -1);
		}
	}
	if (find_player_position(data) == -1)
		return (ft_printf("Error\nNo player position found\n"), -1);
	return (0);
}

int	find_player_position(t_data *data)
{
	int	x;
	int	y;

	for (y = 0; y < data->map_height; y++)
	{
		for (x = 0; x < data->map_width; x++)
		{
			if (ft_strchr("NSWE", data->map[y][x]))
			{
				data->pos_x = x + 0.5;
				data->pos_y = y + 0.5;
				orient_player(data, data->map[y][x]);
				return (0);
			}
		}
	}
	return (-1);
}

int	orient_player(t_data *data, char player_char)
{
	if (player_char == 'N')
	{
		data->dir_x = 0.0;
		data->dir_y = -1.0;
		data->plane_x = 0.66;
		data->plane_y = 0.0;
	}
	else if (player_char == 'S')
	{
		data->dir_x = 0.0;
		data->dir_y = 1.0;
		data->plane_x = -0.66;
		data->plane_y = 0.0;
	}
	else if (player_char == 'E')
	{
		data->dir_x = 1.0;
		data->dir_y = 0.0;
		data->plane_x = 0.0;
		data->plane_y = 0.66;
	}
	else if (player_char == 'W')
	{
		data->dir_x = -1.0;
		data->dir_y = 0.0;
		data->plane_x = 0.0;
		data->plane_y = -0.66;
	}
	return (0);
}

void	free_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
			free(array[i++]);
		free(array);
	}
}

char	**ft_realloc(char **array, int *len, int size, void *item)
{
	char	**new_array;
	int		i;

	if (!array)
	{
		new_array = malloc(sizeof(char *) * (size + 1));
		if (!new_array)
			return (NULL);
		new_array[size] = item;
		new_array[size + 1] = NULL;
		*len = size + 1;
		return (new_array);
	}
	new_array = realloc(array, sizeof(char *) * (*len + 1));
	if (!new_array)
		return (NULL);
	new_array[*len] = item;
	new_array[*len + 1] = NULL;
	*len += 1;
	return (new_array);
}
