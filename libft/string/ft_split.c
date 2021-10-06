/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:29:23 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:25 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_move_to_next_block(const char **s, char c)
{
	size_t			len;

	while (**s && **s == c)
		(*s)++;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	return (len);
}

static size_t	ft_count_blocks(const char *s, char c)
{
	size_t			count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void		ft_freetab(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	block_len;
	size_t	blocks;

	if (!s)
		return (NULL);
	blocks = ft_count_blocks(s, c);
	if (!(tab = (char**)ft_calloc((blocks + 1), sizeof(*tab))))
		return (NULL);
	i = 0;
	while (i++ < blocks)
	{
		block_len = ft_move_to_next_block(&s, c);
		tab[i - 1] = (char*)malloc(sizeof(**tab) * (block_len + 1));
		if (!tab[i - 1])
		{
			ft_freetab(tab);
			return (0);
		}
		ft_strlcpy(tab[i - 1], s, block_len + 1);
		s += block_len + 1;
	}
	tab[i - 1] = 0;
	return (tab);
}
