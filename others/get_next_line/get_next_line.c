/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:56:07 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/14 10:39:05 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* generate_line allocates memory for the 
* line to be returned by get_next_line.  
* It calculates the length of the line by 
* iterating through the linked list 
* stash, counting characters until it finds a newline or reaches the end.  
* It allocates memory of size len + 1 to 
* fit the entire line plus null terminator.
*/
void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

/*
* clean_stash removes the already read part of the stash linked list.  
* It allocates a new list node, copies the remaining unread part of the last
* node's content to the new node, frees the old stash list and sets the new 
* node as the stash.
*/
void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * (ft_strlen(last->content) - i
				+ 1));
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

/*
* Adds a new node to the end of the stash linked list containing the 
* contents of buff up to readed bytes.
* Allocates memory for the new node and copies buff into it.
* Links the new node to the end of the list.
*/
void	more_stash(t_list **stash, char *buff, int readed)
{
	int		i;
	t_list	*last;
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return ;
	newnode->next = NULL;
	newnode->content = malloc(sizeof(char) * (readed + 1));
	if (newnode->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < readed)
	{
		newnode->content[i] = buff[i];
		i++;
	}
	newnode->content[i] = '\0';
	if (!*stash)
	{
		*stash = newnode;
		return ;
	}
	last = ft_lstlast(*stash);
	last->next = newnode;
}

/*
 * Reads from the given file descriptor into the stash 
 * until a newline is encountered or EOF is reached.
 * Allocates a buffer, reads up to BUFFER_SIZE bytes 
 * into it, adds it to the stash with more_stash(), 
 * then frees the buffer. Repeats until newline or EOF.
 * Returns without doing anything if the read fails or malloc fails.
 */
void	read_and_stash(int fd, t_list **stash)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (!check_newline(*stash) && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buff);
			if (readed == -1)
				free_stash(*stash);
			*stash = NULL;
			return ;
		}
		buff[readed] = '\0';
		more_stash(stash, buff, readed);
		free(buff);
	}
}

/**
 * get_next_line - Reads the next line from the given file descriptor.
 * fd: The file descriptor to read from.
 *
 * Iteratively reads from thef ile descriptor into a linked list buffer 
 * (stash) until a newline is found or EOF is reached. Returns the line 
 * read as a null-terminated string (with newline).
 * Returns NULL if read error, malloc fails, or EOF with no bytes read.
 * Uses a static stash to enable reading multiple fds with one call.
 */
char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stash(fd, &stash);
	if (!stash)
		return (NULL);
	line_out(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/*
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("twolines.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	if (line == NULL)
	free(line);
	return (0);
}
*/