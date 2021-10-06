/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:59:43 by matrus            #+#    #+#             */
/*   Updated: 2020/07/23 12:53:28 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_next_line(int fd, char **line)
{
	static t_buff_list	*buff_list = NULL;
	t_buff_list			*cur_buff;
	int					ret_val;

	if (!(cur_buff = is_fd_in_buff_list(buff_list, fd)))
	{
		if (!(cur_buff = new_buff(fd, &buff_list)))
			return (-2);
		lst_push(&buff_list, cur_buff);
	}
	cur_buff->len_total = 0;
	*line = NULL;
	while ((analyse_buf(cur_buff)))
	{
		if (!(*line = ft_realloc(*line, cur_buff->len_total + 1,
			cur_buff->len_total - cur_buff->len)))
			return (del_buff_from_list(cur_buff) - 2);
		copy_buff_to_line(*line, cur_buff);
		if ((ret_val = need_return(cur_buff, *line)))
			return (ret_val - 1);
	}
	return (-1);
}

/*
**		analys_buf function analyses:
**		1 is buff run out, if yes reads new portion
**		2 how much bytes till next NL or EOF to copy
**		3 understands NL or EOF were reached
**		4 counts total *line length (if line continues on next buff portion)
*/

int			analyse_buf(t_buff_list *cur_buff)
{
	cur_buff->end = BUFF_NO_END;
	if (!(cur_buff->i % BUFFER_SIZE))
	{
		cur_buff->readed = read(cur_buff->fd, cur_buff->buff, BUFFER_SIZE);
		cur_buff->i = 0;
	}
	if (cur_buff->readed < 0)
		return (del_buff_from_list(cur_buff));
	if (cur_buff->readed < BUFFER_SIZE)
		cur_buff->end = BUFF_END_EOF;
	cur_buff->len = 0;
	while (cur_buff->i < cur_buff->readed)
	{
		if (cur_buff->buff[cur_buff->i] == '\n')
		{
			cur_buff->end = BUFF_END_NL;
			break ;
		}
		cur_buff->i++;
		cur_buff->len++;
	}
	cur_buff->len_total += cur_buff->len;
	return (1);
}

void		copy_buff_to_line(char *line, t_buff_list *cur_buff)
{
	size_t cpy;

	cpy = cur_buff->len;
	while (cpy > 0)
	{
		line[cur_buff->len_total - cpy] = cur_buff->buff[cur_buff->i - cpy];
		cpy--;
	}
}

t_buff_list	*is_fd_in_buff_list(t_buff_list *buff_list, int fd)
{
	while (buff_list)
	{
		if (buff_list->fd == fd)
			return (buff_list);
		buff_list = buff_list->next;
	}
	return (NULL);
}

/*
**		need_return func analyses which value GNL should return
**		also it do some util staff in case of:
**		1 fd == stdin
**		2 NL or EOF reached
*/

int			need_return(t_buff_list *cur_buff, char *line)
{
	int	ret_val;

	if (cur_buff->end == BUFF_NO_END)
		return (0);
	line[cur_buff->len_total] = '\0';
	ret_val = cur_buff->end;
	if (cur_buff->end == BUFF_END_NL)
	{
		if (cur_buff->fd == 0 &&
		(size_t)cur_buff->readed == cur_buff->len + 1)
			cur_buff->i = 0;
		else
			cur_buff->i++;
	}
	else
		del_buff_from_list(cur_buff);
	return (ret_val);
}
