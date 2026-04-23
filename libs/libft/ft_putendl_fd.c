/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    ft_putendl_fd.c                                       +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/20 11:11:04 by lucas                  ##+              */
/*    Updated: 2026/04/20 11:11:04 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
