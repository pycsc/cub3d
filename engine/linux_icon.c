/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    linux_icon.c                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 16:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/09 16:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct s_xvar
{
	Display	*display;
}	t_xvar;

typedef struct s_win_list
{
	Window	window;
}	t_win_list;

typedef struct s_img_lib
{
	void	*image;
	char	*ptr;
	int		bpp;
	int		sl;
	int		ed;
	int		w;
	int		h;
}	t_img_lib;

static void	fill_icon_data(t_img_lib *img, long *data)
{
	int				x;
	int				y;
	unsigned int	col;

	data[0] = img->w;
	data[1] = img->h;
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			col = *(unsigned int *)(img->ptr + (y * img->sl + \
				x * (img->bpp / 8)));
			data[2 + y * img->w + x] = (long)col;
			x++;
		}
		y++;
	}
}

void	set_platform_icon(t_data *data, const char *path)
{
	t_img_lib	img;
	long		*icon_data;
	Atom		icon_atom;
	t_xvar		*xvar;
	t_win_list	*win;

	img.image = mlx_xpm_file_to_image(data->mlx, (char *)path, &img.w, &img.h);
	if (!img.image)
		return ;
	img.ptr = mlx_get_data_addr(img.image, &img.bpp, &img.sl, &img.ed);
	icon_data = malloc(sizeof(long) * (2 + img.w * img.h));
	if (!icon_data)
		return (void)mlx_destroy_image(data->mlx, img.image);
	fill_icon_data(&img, icon_data);
	xvar = (t_xvar *)data->mlx;
	win = (t_win_list *)data->win;
	icon_atom = XInternAtom(xvar->display, "_NET_WM_ICON", False);
	XChangeProperty(xvar->display, win->window, icon_atom, XA_CARDINAL, 32, \
		PropModeReplace, (unsigned char *)icon_data, 2 + img.w * img.h);
	free(icon_data);
	mlx_destroy_image(data->mlx, img.image);
}
