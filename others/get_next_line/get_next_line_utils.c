/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:55:42 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/14 10:39:37 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

/*
 * check_newline - Checks if newline '\n' exists in the stash linked list.
 * stash: Pointer to the head of the stash linked list.
 *
 * Iterates through the stash list from tail to head checking each 
 * content string for a newline character.
 * Returns 1 if newline found, 0 otherwise.
 */
int	check_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = ft_lstlast(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

/*
 * line_out - Copies the next line from the stash into the line buffer.
 * stash: Pointer to head of stash linked list.
 * line: Pointer to line buffer to copy into.
 * 
 * Iterates stash to find next newline. Copies characters from stash nodes
 * into line buffer until newline or end. Null terminates line buffer.
 */
void	line_out(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

/*
 * free_stash - Frees the memory allocated for the stash linked list.
 * stash: Pointer to the head of the stash list.
 * 
 * Iterates through the stash list, freeing the content and node for 
 * each element.
 */
void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}