/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:12:28 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptrs;
	char	ch;

	ch = (unsigned char)c;
	ptrs = (char*)s;
	i = 0;
	while (n > i)
	{
		ptrs[i] = ch;
		i++;
	}
	return (s);
}
