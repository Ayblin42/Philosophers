/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:02:17 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 23:02:17 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_ac(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count + 1);
}

static char	*get_next_word(int *index, const char *str, char c)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	while (str[*index] == c)
		(*index)++;
	while (str[*index + len] && str[*index + len] != c)
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i++] = str[*index];
		*index = *index + 1;
	}
	res[i] = 0;
	return (res);
}

static void	free_exit(char **val, int size)
{
	while (size >= 0)
	{
		free(val[size]);
		size--;
	}
	free(val);
	val = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		ac;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	ac = get_ac(s, c);
	res = malloc(ac * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < ac - 1)
	{
		res[i] = get_next_word(&j, s, c);
		if (res[i] == NULL)
			return (free_exit(res, i), NULL);
		i++;
	}
	res[i] = 0;
	return (res);
}
