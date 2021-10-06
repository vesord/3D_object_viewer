/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:43:32 by matrus            #+#    #+#             */
/*   Updated: 2020/05/08 21:40:22 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MIN_LONG_DIV_TEN -922337203685477580
#define MAX_LONG_DIV_TEN 922337203685477580
#define MAX_LONG_ATOI 9223372036854775807
#define MIN_LONG_ATOI -9223372036854775807

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static int	ft_read_nb_atoi(const char *str, int sign)
{
	long long	res;
	int			i;

	i = 0;
	res = 0;
	while (str[i] != '\0')
		if ((str[i] >= '0') && (str[i]) <= '9')
		{
			if (res * sign <= MAX_LONG_DIV_TEN
			&& res * sign >= MIN_LONG_DIV_TEN)
				res *= 10;
			else
				return (res * sign < 0 ? 0 : -1);
			if (res * sign <= MAX_LONG_ATOI - (str[i] - '0')
			&& res * sign >= MIN_LONG_ATOI - 1 + (str[i] - '0'))
				res += str[i] - '0';
			else
				return (res * sign < 0 ? 0 : -1);
			i++;
		}
		else
			break ;
	return ((int)(res * sign));
}

int			ft_atoi(const char *nptr)
{
	int i;
	int sign;

	i = 0;
	sign = 1;
	while (ft_is_space(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (nptr[i] == '+')
		i++;
	return (ft_read_nb_atoi(nptr + i, sign));
}
