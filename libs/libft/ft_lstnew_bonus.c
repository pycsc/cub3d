/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    ft_lstnew_bonus.c                                     +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/20 11:11:04 by lucas                  ##+              */
/*    Updated: 2026/04/20 11:11:04 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
