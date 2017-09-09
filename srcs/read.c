/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 18:33:33 by liton             #+#    #+#             */
/*   Updated: 2017/09/09 22:09:21 by liton            ###   ########.fr       */
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
	if ((*file)->next->first != 1)
		*file = (*file)->next;
	else
		*file = (*file)->prev;
	(*file)->cursor = 1;
	delete_file(&tmp, begin);
}

static void		up(t_files **file, int count)
{
	t_files		*tmp;
	int			cnt;

	if ((*file)->first == 1)
		return ;
	cnt = 0;
	tmp = *file;
	while (cnt < count)
	{
		if (tmp->first == 1)
			return ;
		tmp = tmp->prev;
		++cnt;
	}
	(*file)->cursor = 0;
	*file = tmp;
	(*file)->cursor = 1;
}

static void		down(t_files **file, int count)
{
	t_files		*tmp;
	int			cnt;

	cnt = 0;
	tmp = *file;
	while (cnt < count)
	{
		tmp = tmp->next;
		++cnt;
		if (tmp->first == 1)
			return ;
	}
	(*file)->cursor = 0;
	*file = tmp;
	(*file)->cursor = 1;
}

void			read_buff(t_files **file, t_files **begin, int count)
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
	else if (buff[2] == 65)
		up(file, count);
	else if (buff[2] == 66)
		down(file, count);
}
