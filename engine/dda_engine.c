/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    dda_engine.c                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 15:45:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 15:45:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dda(t_data *data, double rx, double ry, t_dda *d)
{
	d->rx = rx; d.ry = ry;
	d->dd[0] = fabs(1 / rx); d->dd[1] = fabs(1 / ry);
	d->map[0] = (int)data->player.x; d->map[1] = (int)data->player.y;
	d->step[0] = (rx < 0) ? -1 : 1; d->step[1] = (ry < 0) ? -1 : 1;
	if (rx < 0) d->sd[0] = (data->player.x - d->map[0]) * d->dd[0];
	else d->sd[0] = (d->map[0] + 1.0 - data->player.x) * d->dd[0];
	if (ry < 0) d->sd[1] = (data->player.y - d->map[1]) * d->dd[1];
	else d->sd[1] = (d->map[1] + 1.0 - data->player.y) * d->dd[1];
}

static void	dda_loop(t_data *data, t_dda *d)
{
	while (data->map[d->map[1]][d->map[0]] != '1')
	{
		if (!d->hit_coin && data->map[d->map[1]][d->map[0]] == '2')
		{
			d->hit_coin = 1;
			d->coin_pwd = (d->side == 0) ? \
				(d->map[0] - data->player.x + (1 - d->step[0]) / 2) / d->rx : \
				(d->map[1] - data->player.y + (1 - d->step[1]) / 2) / d->ry;
			d->coin_wall_x = (d->side == 0) ? \
				data->player.y + d->coin_pwd * d->ry : \
				data->player.x + d->coin_pwd * d->rx;
			d->coin_wall_x -= floor(d->coin_wall_x);
		}
		if (d->sd[0] < d->sd[1] && (d->side = 0))
		{
			d->sd[0] += d->dd[0];
			d->map[0] += d->step[0];
		}
		else if ((d->side = 1))
		{
			d->sd[1] += d->dd[1];
			d->map[1] += d->step[1];
		}
	}
}

void	perform_dda(t_data *data, double rx, double ry, int x)
{
	t_dda	d;

	ft_memset(&d, 0, sizeof(t_dda));
	init_dda(data, rx, ry, &d);
	dda_loop(data, &d);
	if (d.side == 0)
		d.pwd = (d.map[0] - data->player.x + (1 - d.step[0]) / 2) / rx;
	else
		d.pwd = (d.map[1] - data->player.y + (1 - d.step[1]) / 2) / ry;
	draw_line_textured(data, x, &d);
}
