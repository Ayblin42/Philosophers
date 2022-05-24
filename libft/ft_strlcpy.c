/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:25:41 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 16:25:41 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(src);
	j = -1;
	if (i + 1 < size)
	{
		while (++j < i + 1)
			dst[j] = src[j];
	}
	else if (size > 0)
	{
		while (++j < size - 1)
			dst[j] = src[j];
		dst[j] = 0;
	}
	return (i);
}
