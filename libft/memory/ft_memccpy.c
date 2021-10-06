/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:30:18 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptrdest;
	const unsigned char	*ptrsrc;
	unsigned char		uc;

	i = 0;
	ptrdest = (unsigned char*)dest;
	ptrsrc = (const unsigned char*)src;
	uc = (unsigned char)c;
	while (n > i)
	{
		ptrdest[i] = ptrsrc[i];
		if (ptrsrc[i] == uc)
			return ((void *)(dest + i + 1));
		i++;
	}
	return (0);
}
