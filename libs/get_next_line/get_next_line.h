/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    get_next_line.h                                       +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/23 20:00:00 by lucas                  ##+              */
/*    Updated: 2026/05/08 08:00:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
void	*gnl_calloc(size_t count, size_t size);
void	gnl_bzero(void *s, size_t n);
void	*gnl_memset(void *b, int c, size_t len);

#endif
