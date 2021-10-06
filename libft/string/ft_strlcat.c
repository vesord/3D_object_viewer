/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:22:26 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:25 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[i] && size > i)
		i++;
	if (size < i + 1)
		return (size + ft_strlen(src));
	while (src[j])
	{
		if (size > i + j + 1)
			dst[j + i] = src[j];
		j++;
	}
	if (size > i + j + 1)
		dst[i + j] = '\0';
	else
		dst[size - 1] = '\0';
	return (i + j);
}
