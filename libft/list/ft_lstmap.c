/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:25:28 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newlst;

	if (!lst || !f || !del)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (0);
	if (lst->next)
	{
		newlst->next = ft_lstmap(lst->next, f, del);
		if (newlst->next == 0)
		{
			ft_lstdelone(newlst, del);
			return (0);
		}
	}
	return (newlst);
}
