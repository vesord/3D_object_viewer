/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:32:42 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*ptrdest;
	const char	*ptrsrc;

	if (dest == src)
		return (dest);
	i = 0;
	ptrdest = (char*)dest;
	ptrsrc = (const char*)src;
	while (n > i)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	return (dest);
}
