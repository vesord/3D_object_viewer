/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:46:07 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		ch;
	const unsigned char	*ptrs;

	ch = (unsigned char)c;
	ptrs = (const unsigned char*)s;
	while (n--)
		if (*ptrs++ == ch)
			return ((void*)--ptrs);
	return (0);
}
