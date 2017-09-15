/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 18:33:33 by liton             #+#    #+#             */
/*   Updated: 2017/09/15 04:10:24 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		right(void)
{
	global->file->cursor = 0;
	global->file = global->file->next;
	global->file->cursor = 1;
}

static void		left(void)
{
	global->file->cursor = 0;
	global->file = global->file->prev;
	global->file->cursor = 1;
}

static void		select_mode(void)
{
	global->file->cursor = 0;
	if (global->file->reverse == 0)
		global->file->reverse = 1;
	else
		global->file->reverse = 0;
	global->file = global->file->next;
	global->file->cursor = 1;
}

static void		delete_mode(void)
{
	t_files		*tmp;

	tmp = global->file;
	if (global->file->next->first != 1)
		global->file = global->file->next;
	else
		global->file = global->file->prev;
	global->file->cursor = 1;
	delete_file(&tmp);
}

static void		up(void)
{
	t_files		*tmp;
	int			cnt;

	cnt = 0;
	tmp = global->file;
	while (cnt < global->fmt->count)
	{
		if (tmp->first == 1)
			return ;
		tmp = tmp->prev;
		++cnt;
	}
	global->file->cursor = 0;
	global->file = tmp;
	global->file->cursor = 1;
}

static void		down(void)
{
	t_files		*tmp;
	int			cnt;

	cnt = 0;
	tmp = global->file;
	while (cnt < global->fmt->count)
	{
		tmp = tmp->next;
		++cnt;
		if (tmp->first == 1)
			return ;
	}
	global->file->cursor = 0;
	global->file = tmp;
	global->file->cursor = 1;
}

void			read_buff(void)
{
	char	buff[3 + 1];

	read(0, buff, 3);
	while (global->file->cursor != 1)
		global->file = global->file->next;
	if (buff[2] == 67)
		right();
	else if (buff[2] == 68)
		left();
	else if (buff[0] == 32)
		select_mode();
	else if (buff[0] == 127)
		delete_mode();
	else if (buff[2] == 65)
		up();
	else if (buff[2] == 66)
		down();
}
