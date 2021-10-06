/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:12:06 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:26 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;
	char	*strimmed;

	if (!s1)
		return (NULL);
	left = 0;
	right = ft_strlen(s1);
	while (s1[left] && ft_strchr(set, s1[left]))
		left++;
	while (right && right - 1 && ft_strchr(set, s1[right - 1]))
		right--;
	if (!(right - 1))
		right = left;
	strimmed = (char*)malloc(sizeof(*strimmed) * (right - left + 1));
	if (!strimmed)
		return (0);
	strimmed[right - left] = '\0';
	while (right - left)
	{
		strimmed[right - left - 1] = s1[right - 1];
		right--;
	}
	return (strimmed);
}
