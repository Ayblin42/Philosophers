/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:07:44 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 16:07:44 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ucsrc;
	unsigned char	*ucdest;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	ucsrc = (unsigned char *)src;
	ucdest = (unsigned char *)dest;
	if (ucdest > ucsrc)
	{
		while (n--)
			ucdest[n] = ucsrc[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			ucdest[i] = ucsrc[i];
	}
	return (dest);
}
