/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 11:01:22 by matrus            #+#    #+#             */
/*   Updated: 2020/07/23 12:53:30 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff_list	*new_buff(int fd, t_buff_list **static_head)
{
	t_buff_list *new_buff;

	if (fd < 0)
		return (NULL);
	if (!(new_buff = (t_buff_list*)malloc(sizeof(t_buff_list))))
		return (NULL);
	if (!(new_buff->buff = (char*)malloc(BUFFER_SIZE)))
	{
		free(new_buff);
		return (NULL);
	}
	new_buff->fd = fd;
	new_buff->len = 0;
	new_buff->len_total = 0;
	new_buff->end = BUFF_NO_END;
	new_buff->readed = 0;
	new_buff->i = 0;
	new_buff->next = NULL;
	new_buff->prev = NULL;
	new_buff->head = static_head;
	return (new_buff);
}

void		lst_push(t_buff_list **head, t_buff_list *elem)
{
	t_buff_list *tmp;

	if (!*head)
	{
		*head = elem;
		*(elem->head) = *head;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->prev = tmp;
	}
}

void		*ft_realloc(void *ptr, size_t new_size, size_t prev_size)
{
	char	*new_ptr;
	size_t	i;

	if (!(new_ptr = (char*)malloc(new_size)))
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (new_ptr);
	i = 0;
	while (i < prev_size)
	{
		new_ptr[i] = ((char*)ptr)[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

/*
**		del_buff_list deletes element from buff list
**		it appears in case
**		1 EOF reached
**		2 read returned -1
**		3 realloc does not succeed
**		always returns 0
*/

int			del_buff_from_list(t_buff_list *buff)
{
	if (*(buff->head) != buff)
		buff->prev->next = buff->next;
	else
	{
		if (buff->next)
			buff->next->prev = NULL;
		*(buff->head) = buff->next;
	}
	free(buff->buff);
	free(buff);
	return (0);
}
