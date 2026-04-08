/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    raycasting_engine.c                                   +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/08 06:25:19 by lucas                  ##+              */
/*    Updated: 2026/04/08 06:25:19 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

/* Raycasting engine for 3D wall rendering */

#include "../include/cub3d.h"
#include <math.h>

void	init_raycasting(t_data *data)
{
	double	camera_x;

	if (!data->mlx)
		return;
}

void	raycasting(t_data *data)
{
	int	x;
	int	draw_start;
	int	draw_end;
	int	line_height;
	double	camera_x;
	double	*ray_dir;
	double	*delta_dist;
	int	*step;
	int	*side;
	double	*perp_wall_dist;
	int	*wall_x;
	double	*wall_x_f;
	int	*color;
	void	*texture;

	if (!data->img)
		return;
	for (x = 0; x < WIDTH; x++)
	{
		camera_x = 2.0 * x / (double)WIDTH - 1.0;
		ray_dir = malloc(sizeof(double) * 2);
		if (!ray_dir) continue;
		ray_dir[0] = data->dir_x + data->plane_x * camera_x;
		ray_dir[1] = data->dir_y + data->plane_y * camera_x;

		delta_dist = malloc(sizeof(double) * 2);
		if (!delta_dist) { free(ray_dir); continue; }
		delta_dist[0] = fabs(1.0 / ray_dir[0]);
		delta_dist[1] = fabs(1.0 / ray_dir[1]);

		step = malloc(sizeof(int) * 2);
		if (!step) { free(ray_dir); free(delta_dist); continue; }
		step[0] = (ray_dir[0] < 0) ? -1 : 1;
		step[1] = (ray_dir[1] < 0) ? -1 : 1;

		side = malloc(sizeof(int) * 2);
		if (!side) { free(ray_dir); free(delta_dist); free(step); continue; }

		*side = 0;
		if (ray_dir[0] < 0)
			step[0] = -1;
		else
			step[0] = 1;
		if (ray_dir[1] < 0)
			step[1] = -1;
		else
			step[1] = 1;

		perp_wall_dist = malloc(sizeof(double) * 2);
		if (!perp_wall_dist) { free(ray_dir); free(delta_dist); free(step); free(side); continue; }

		double	*map_x = malloc(sizeof(double));
		double	*map_y = malloc(sizeof(double));
		if (!map_x || !map_y) { free(ray_dir); free(delta_dist); free(step); free(side); free(perp_wall_dist); continue; }

		*map_x = (int)data->pos_x;
		*map_y = (int)data->pos_y;
		*perp_wall_dist = 0.0;

		while ((*map_x >= 0 && *map_x < data->map_width) &&
			   (*map_y >= 0 && *map_y < data->map_height) &&
			   (data->map[(int)*map_y][(int)*map_x] == '0' ||
				ft_strchr("NSWE", data->map[(int)*map_y][(int)*map_x])))
		{
			*perp_wall_dist += step[0] < 0 ? delta_dist[0] : -delta_dist[0];
			*map_x += step[0];
			*perp_wall_dist += step[1] < 0 ? delta_dist[1] : -delta_dist[1];
			*map_y += step[1];
		}

		if (*map_x < 0 || *map_x >= data->map_width ||
			*map_y < 0 || *map_y >= data->map_height ||
			data->map[(int)*map_y][(int)*map_x] == '0')
		{
			free(ray_dir); free(delta_dist); free(step); free(side); free(perp_wall_dist); free(map_x); free(map_y);
			continue;
		}

		if (step[0] < 0)
			*side = 2;
		else
			*side = 4;

		if (ray_dir[0] < 0)
			*side = *side + 1;
		else
			*side = *side + 3;

		*perp_wall_dist = (*perp_wall_dist < 0) ? -(*perp_wall_dist) : *perp_wall_dist;
		if (side[0] || side[1])
			*perp_wall_dist *= 0.66;

		line_height = (int)(HEIGHT / *perp_wall_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

		wall_x_f = malloc(sizeof(double));
		if (!wall_x_f) { free(ray_dir); free(delta_dist); free(step); free(side); free(perp_wall_dist); free(map_x); free(map_y); continue; }
		if (*side < 4)
			*wall_x_f = data->pos_y + *perp_wall_dist * ray_dir[1];
		else
			*wall_x_f = data->pos_x + *perp_wall_dist * ray_dir[0];
		*wall_x_f -= floor(*wall_x_f);

		wall_x = malloc(sizeof(int));
		if (!wall_x) { free(ray_dir); free(delta_dist); free(step); free(side); free(perp_wall_dist); free(map_x); free(map_y); free(wall_x_f); continue; }
		*wall_x = (int)(*wall_x_f * (double)data->img_width);
		if (side == 0 || side == 2) *wall_x = (int)(data->img_width - *wall_x);

		if (side == 0 || side == 1)
			texture = data->south_texture;
		else
			texture = data->north_texture;

		if (side >= 0 && side <= 4)
			color = get_texture_color(texture, *wall_x, draw_start);
		else
			color = data->wall_color;

		color = malloc(sizeof(int));
		if (!color) continue;

		while (draw_start < draw_end && draw_start < HEIGHT)
		{
			*(int*)(data->img_data + draw_start * data->line_length + x * (data->bits_per_pixel / 8)) = *color;
			draw_start++;
		}

		while (draw_end < HEIGHT && draw_end >= 0)
		{
			*(int*)(data->img_data + draw_end * data->line_length + x * (data->bits_per_pixel / 8)) = *color;
			draw_end++;
		}

		free(ray_dir);
		free(delta_dist);
		free(step);
		free(side);
		free(perp_wall_dist);
		free(map_x);
		free(map_y);
		free(wall_x_f);
		free(wall_x);
		free(color);

		draw_bottom_floor_ceiling(data);
	}
}

void	draw_bottom_floor_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	if (!data->img) return;

	floor_color = data->floor_color;
	ceiling_color = data->ceiling_color;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (y < HEIGHT / 2)
				*(int*)(data->img_data + y * data->line_length + x * (data->bits_per_pixel / 8)) = ceiling_color;
			else
				*(int*)(data->img_data + y * data->line_length + x * (data->bits_per_pixel / 8)) = floor_color;
		}
	}
}

int	get_texture_color(void *texture, int x, int y)
{
	int	*color;

	if (!texture) return (-1);
	color = malloc(sizeof(int));
	if (!color) return (-1);
	*color = (0xFFFFFF);
	return *color;
}
