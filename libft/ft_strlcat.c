/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:26:14 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 16:26:14 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	length;

	length = 0;
	i = 0;
	while (dst[length] && length < size)
		length++;
	while (src[i] && size && length + i < size - 1)
	{
		dst[length + i] = src[i];
		i++;
	}
	if (length < size)
		dst[length + i] = 0;
	i = 0;
	while (src[i])
		i++;
	return (length + i);
}
