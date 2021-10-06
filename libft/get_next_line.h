/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 11:04:58 by matrus            #+#    #+#             */
/*   Updated: 2020/06/14 17:34:58 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# define BUFF_NO_END 0
# define BUFF_END_EOF 1
# define BUFF_END_NL 2

typedef struct	s_buff_list
{
	struct s_buff_list	*next;
	struct s_buff_list	*prev;
	struct s_buff_list	**head;
	char				*buff;
	int					fd;
	ssize_t				i;
	size_t				len;
	size_t				len_total;
	int					end;
	ssize_t				readed;
}				t_buff_list;

int				get_next_line(int fd, char **line);
int				analyse_buf(t_buff_list *cur_buff);
void			copy_buff_to_line(char *line, t_buff_list *cur_buff);
t_buff_list		*is_fd_in_buff_list(t_buff_list *buff_list, int fd);
int				need_return(t_buff_list *cur_buff, char *line);
t_buff_list		*new_buff(int fd, t_buff_list **static_head);
void			lst_push(t_buff_list **head, t_buff_list *elem);
void			*ft_realloc(void *ptr, size_t new_size, size_t prev_size);
int				del_buff_from_list(t_buff_list *buff);

#endif
