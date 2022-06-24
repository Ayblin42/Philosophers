/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:27:36 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 23:27:36 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reverse_array_malloc(char *array)
{
	char	*new;
	int		end;
	int		i;

	end = ft_strlen(array);
	new = malloc(sizeof(char) * (end + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (--end >= 0)
		new[++i] = array[end];
	new[++i] = 0;
	return (new);
}

static char	*malloc_zero(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	ret[1] = 0;
	return (ret);
}

char	*ft_itoa(int n)
{
	char			ret[12];
	int				i;
	int				sign;
	long int		nb;

	if (n == 0)
		return (malloc_zero());
	nb = (long int)n;
	sign = 1;
	if (nb < 0)
	{
		sign *= -1;
		nb = -nb;
	}
	i = 0;
	while (nb)
	{
		ret[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	if (sign == -1)
		ret[i++] = '-';
	ret[i] = 0;
	return (reverse_array_malloc(ret));
}
