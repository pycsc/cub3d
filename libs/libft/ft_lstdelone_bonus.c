/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    ft_lstdelone_bonus.c                                  +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/20 11:11:04 by lucas                  ##+              */
/*    Updated: 2026/04/20 11:11:04 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
