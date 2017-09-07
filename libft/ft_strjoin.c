/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:50:11 by liton             #+#    #+#             */
/*   Updated: 2017/08/25 04:23:37 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_str = NULL;
	if (s1 == NULL && s2 != NULL)
		new_str = ft_strdup(s2);
	else if (s1 != NULL && s2 == NULL)
		new_str = ft_strdup(s1);
	else if (s1 != NULL && s2 != NULL)
	{
		if (!(new_str = (char*)(malloc)(sizeof(char) *
			ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		while (s1[++i])
			new_str[i] = s1[i];
		while (s2[++j])
			new_str[i++] = s2[j];
		new_str[i] = '\0';
	}
	return (new_str);
}
