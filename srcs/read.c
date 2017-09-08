/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 18:33:33 by liton             #+#    #+#             */
/*   Updated: 2017/09/08 21:08:25 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		right(t_files **file)
{
	(*file)->cursor = 0;
	*file = (*file)->next;
	(*file)->cursor = 1;
}

static void		left(t_files **file)
{
	(*file)->cursor = 0;
	*file = (*file)->prev;
	(*file)->cursor = 1;
}

static void		select_mode(t_files **file)
{
	(*file)->cursor = 0;
	if ((*file)->reverse == 0)
		(*file)->reverse = 1;
	else
		(*file)->reverse = 0;
	*file = (*file)->next;
	(*file)->cursor = 1;

}

static void		delete_mode(t_files **file, t_files **begin)
{
	t_files		*tmp;

	tmp = *file;
	(*file)->next->cursor = 1;
	*file = (*file)->next;
	delete_file(&tmp, begin);
}

void			read_buff(t_files **file, t_files **begin)
{
	char	buff[3 + 1];

	read(0, buff, 3);
	if (buff[2] == 67)
		right(file);
	else if (buff[2] == 68)
		left(file);
	else if (buff[0] == 32)
		select_mode(file);
	else if (buff[0] == 127)
		delete_mode(file, begin);
}
