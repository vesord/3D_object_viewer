/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:14:39 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:25 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*news;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	news = (char*)malloc(sizeof(*news) * (len + 1));
	if (!news)
		return (NULL);
	news[len] = '\0';
	i = 0;
	while (s[i])
	{
		news[i] = s[i];
		i++;
	}
	return (news);
}
