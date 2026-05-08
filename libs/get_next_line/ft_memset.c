/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    ft_memset.c                                           +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 20:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 08:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
