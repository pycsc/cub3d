/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    hud_renderer.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 09:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 14:45:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_rect(t_data *data, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			my_mlx_pixel_put(&data->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_bar(t_data *data, int x, int y, int val, int color)
{
	draw_rect(data, x, y, 100, 12, 0x00222222); // Background
	draw_rect(data, x, y, val, 12, color); // Fill
}

static void	draw_dollar(t_data *data, int x, int y, int color)
{
	draw_rect(data, x + 5, y + 5, 20, 4, color);
	draw_rect(data, x + 5, y + 5, 4, 10, color);
	draw_rect(data, x + 5, y + 13, 20, 4, color);
	draw_rect(data, x + 21, y + 13, 4, 10, color);
	draw_rect(data, x + 5, y + 21, 20, 4, color);
	draw_rect(data, x + 13, y + 2, 4, 26, color);
}

void	draw_hud(t_data *data)
{
	// Health (Top-left) - White
	draw_rect(data, 20, 20, 30, 30, 0x00000000);
	draw_rect(data, 25, 33, 20, 4, 0x00FFFFFF);
	draw_rect(data, 33, 25, 4, 20, 0x00FFFFFF);
	draw_bar(data, 60, 30, data->health, 0x00FFFFFF);

	// Ammo (Below Health) - White
	draw_rect(data, 20, 60, 30, 30, 0x00000000);
	draw_rect(data, 25, 65, 3, 15, 0x00FFFFFF);
	draw_rect(data, 31, 65, 3, 15, 0x00FFFFFF);
	draw_rect(data, 37, 65, 3, 15, 0x00FFFFFF);
	draw_bar(data, 60, 70, data->ammo, 0x00FFFFFF);

	// Score (Top-right) - Gray
	draw_rect(data, 680, 20, 30, 30, 0x00333333);
	draw_dollar(data, 680, 20, 0x00666666);
	draw_rect(data, 720, 30, 60, 12, 0x00666666);
}
