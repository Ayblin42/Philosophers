/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:44:00 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/05/06 12:46:11 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *str, char *add)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	j = -1;
	while (add[++j])
		str[i + j] = add[j];
	str[i + j] = 0;
}
