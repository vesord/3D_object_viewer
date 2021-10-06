/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:15:47 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 19:15:49 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The function creates a copy of a two-dimensional array of strings that
** ends in NULL. The function is protected from leaks.
*/

char	**ft_tabdub(const char **tab)
{
	char		**new_tab;
	char		**tab_end;
	size_t		i;

	tab_end = (char **)tab;
	while (*tab_end)
		++tab_end;
	i = tab_end - (char **)tab;
	if ((new_tab = ft_calloc(sizeof(char *), i + 1)))
	{
		new_tab[i] = NULL;
		while (i--)
		{
			if (!(new_tab[i] = ft_strdup(tab[i])))
			{
				while (new_tab[i])
					free(new_tab[i++]);
				free(new_tab);
				new_tab = NULL;
				break ;
			}
		}
	}
	return (new_tab);
}
