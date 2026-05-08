/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    ft_calloc.c                                           +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 20:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 08:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	gnl_bzero(ptr, count * size);
	return (ptr);
}
