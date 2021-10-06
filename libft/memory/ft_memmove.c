/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:51:54 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*ptrdest;
	const char	*ptrsrc;

	if (dest == src)
		return (dest);
	i = 0;
	ptrdest = (char*)dest;
	ptrsrc = (const char*)src;
	if (ptrdest < ptrsrc)
		while (n > i)
		{
			ptrdest[i] = ptrsrc[i];
			i++;
		}
	else
		while (n > i)
		{
			ptrdest[n - 1 - i] = ptrsrc[n - 1 - i];
			i++;
		}
	return (dest);
}
