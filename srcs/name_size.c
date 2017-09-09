/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:16:16 by liton             #+#    #+#             */
/*   Updated: 2017/09/09 19:55:07 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_format	*name_size(t_files *file)
{
	int				save;
	int				exit;
	t_format		*fmt;

	exit = 1;
	if (!(fmt = (t_format*)malloc(sizeof(t_format))))
		return (NULL);
	fmt->count = 0;
	fmt->row = 0;
	fmt->nb_list = 0;
	fmt->len_max = 0;
	fmt->word_max = 0;
	fmt->nbl_save = 0;
	while (exit != 0)
	{
		++fmt->nbl_save;
		if ((save = ft_strlen(file->name)) > fmt->len_max)
			fmt->len_max = save;
		file = file->next;
		if (file->first == 1)
			exit = 0;
	}
	fmt->word_max = fmt->len_max;
	fmt->len_max += 3;
	return (fmt);
}
