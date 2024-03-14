/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:05:07 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/14 10:39:14 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
/*# include <stdio.h>*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

void				free_stash(t_list *stash);
void				clean_stash(t_list **stash);
void				more_stash(t_list **stash, char *buff, int readed);
void				read_and_stash(int fd, t_list **stash);
char				*get_next_line(int fd);
void				generate_line(char **line, t_list *stash);
void				line_out(t_list *stash, char **line);
t_list				*ft_lstlast(t_list *stash);
int					check_newline(t_list *stash);
int					ft_strlen(char *str);

#endif