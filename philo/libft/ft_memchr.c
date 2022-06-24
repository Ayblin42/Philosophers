/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:10:51 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 17:10:51 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ucs;
	size_t			i;

	i = 0;
	ucs = (unsigned char *)s;
	while (i < n)
	{
		if (ucs[i] == (unsigned char)c)
			return (ucs + i);
		i++;
	}
	return (NULL);
}
