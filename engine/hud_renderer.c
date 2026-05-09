/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    hud_renderer.c                                        +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/08 09:30:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 16:30:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	draw_rect(t_data *data, int x, int y, int w, int h, int color)
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

static int	is_d(int d, int *list)
{
	int	i;

	i = 0;
	while (list[i] != -1)
	{
		if (d == list[i])
			return (1);
		i++;
	}
	return (0);
}

static void	draw_digit(t_data *data, int x, int y, int digit)
{
	int	t[] = {0, 2, 3, 5, 6, 7, 8, 9, -1};
	int	tl[] = {0, 4, 5, 6, 8, 9, -1};
	int	tr[] = {0, 1, 2, 3, 4, 7, 8, 9, -1};
	int	m[] = {2, 3, 4, 5, 6, 8, 9, -1};
	int	bl[] = {0, 2, 6, 8, -1};
	int	br[] = {0, 1, 3, 4, 5, 6, 7, 8, 9, -1};
	int	b[] = {0, 2, 3, 5, 6, 8, 9, -1};

	if (is_d(digit, t)) draw_rect(data, x, y, 10, 2, 0xFFFFFF);
	if (is_d(digit, tl)) draw_rect(data, x, y, 2, 10, 0xFFFFFF);
	if (is_d(digit, tr)) draw_rect(data, x + 8, y, 2, 10, 0xFFFFFF);
	if (is_d(digit, m)) draw_rect(data, x, y + 9, 10, 2, 0xFFFFFF);
	if (is_d(digit, bl)) draw_rect(data, x, y + 10, 2, 10, 0xFFFFFF);
	if (is_d(digit, br)) draw_rect(data, x + 8, y + 10, 2, 10, 0xFFFFFF);
	if (is_d(digit, b)) draw_rect(data, x, y + 18, 10, 2, 0xFFFFFF);
}

static void	draw_number(t_data *data, int x, int y, int num)
{
	if (num >= 10)
		draw_number(data, x - 15, y, num / 10);
	draw_digit(data, x, y, num % 10);
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
	draw_rect(data, 20, 20, 30, 30, 0x00000000);
	draw_rect(data, 25, 33, 20, 4, 0xFFFFFF);
	draw_rect(data, 33, 25, 4, 20, 0xFFFFFF);
	draw_rect(data, 60, 30, 100, 12, 0x222222);
	draw_rect(data, 60, 30, data->health, 12, 0xFFFFFF);
	draw_rect(data, 20, 60, 30, 30, 0x00000000);
	draw_rect(data, 25, 65, 3, 15, 0xFFFFFF);
	draw_rect(data, 31, 65, 3, 15, 0xFFFFFF);
	draw_rect(data, 37, 65, 3, 15, 0xFFFFFF);
	draw_rect(data, 60, 70, 100, 12, 0x222222);
	draw_rect(data, 60, 70, data->ammo, 12, 0xFFFFFF);
	draw_rect(data, 680, 20, 30, 30, 0x00000000);
	draw_dollar(data, 680, 20, 0xFFFFFF);
	draw_number(data, 770, 25, data->score);
}
