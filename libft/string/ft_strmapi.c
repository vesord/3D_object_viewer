/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:24:35 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:25 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*map;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	map = (char*)malloc(sizeof(*map) * (len + 1));
	if (!map)
		return (NULL);
	map[len] = 0;
	i = 0;
	while (len > i)
	{
		map[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (map);
}
