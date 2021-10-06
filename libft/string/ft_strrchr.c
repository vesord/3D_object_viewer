/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:19:43 by matrus            #+#    #+#             */
/*   Updated: 2020/05/09 20:38:36 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char			*t;
	unsigned char	uc;

	uc = (unsigned char)c;
	t = 0;
	while (*s)
	{
		if (*s == uc)
			t = (char*)s;
		s++;
	}
	if (uc == 0)
		return ((char*)s);
	else
		return (t);
}
