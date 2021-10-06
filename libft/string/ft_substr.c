/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:10:58 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:26 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substrl;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	substrl = 0;
	while (s[start + substrl] && len--)
		substrl++;
	substr = (char*)malloc(sizeof(*substr) * (substrl + 1));
	if (!substr)
		return (NULL);
	substr[substrl] = '\0';
	while (substrl)
	{
		substr[substrl - 1] = s[start + substrl - 1];
		substrl--;
	}
	return (substr);
}
