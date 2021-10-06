/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:19:45 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:26 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!*lit)
		return ((char*)big);
	while (len > i)
	{
		if (big[i] == lit[0])
		{
			j = 0;
			while (len > i + j && lit[j] != 0 && lit[j] == big[i + j])
				j++;
			if (lit[j] == 0)
				return ((char*)(big + i));
		}
		i++;
	}
	return (0);
}
