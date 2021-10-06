/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:57:41 by matrus            #+#    #+#             */
/*   Updated: 2020/07/23 12:58:13 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_realloc_tab(void **tab, int prev_size, int need_size)
{
	void	**new_ptr;

	if (!(new_ptr = (void**)malloc(sizeof(void*) * need_size)))
		return (NULL);
	while (need_size > prev_size)
	{
		new_ptr[need_size - 1] = NULL;
		need_size--;
	}
	while (prev_size > 0)
	{
		new_ptr[prev_size - 1] = tab[prev_size - 1];
		prev_size--;
	}
	free(tab);
	return (new_ptr);
}
