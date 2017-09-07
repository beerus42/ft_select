/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 18:58:27 by liton             #+#    #+#             */
/*   Updated: 2017/09/06 18:47:05 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

int				ft_word(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || (str[i] == '\n' && str[i]))
			i++;
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			count++;
			while (str[i] != '\t' && str[i] != '\n' && str[i] != ' ' && str[i])
			{
				i++;
			}
		}
	}
	return (count);
}

static int		ft_strsubi(char *str, int start, int length, char **dest)
{
	int		i;
	int		k;

	k = 0;
	*dest = (char*)malloc(sizeof(char) * (length + 1));
	if (*dest == NULL)
		return (0);
	i = start;
	while (k < length)
	{
		(*dest)[k] = str[i];
		i++;
		k++;
	}
	(*dest)[k] = '\0';
	return (1);
}

void			ft_split(char *str, char ***tab)
{
	int		i;
	int		start;
	char	*dest;
	int		k;

	i = 0;
	start = 0;
	dest = NULL;
	k = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			start = i;
			while (str[i] != '\t' && str[i] != '\n' && str[i] != ' ' && str[i])
				i++;
			ft_strsubi(str, start, i - start, &dest);
			(*tab)[k++] = dest;
		}
	}
	(*tab)[k] = 0;
}

char			**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_word(str) + 1))))
		return (NULL);
	ft_split(str, &tab);
	return (tab);
}
