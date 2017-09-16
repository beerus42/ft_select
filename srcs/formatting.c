/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:57:43 by liton             #+#    #+#             */
/*   Updated: 2017/09/16 04:37:27 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			nb_list(void)
{
	int		exit;

	exit = 1;
	global->fmt->nb_list = 0;
	while (global->file && exit != 0)
	{
		++global->fmt->nb_list;
		global->file = global->file->next;
		if (global->file->first == 1)
			exit = 0;
	}
}

static void			nb_space(char *name)
{
	int		i;

	i = -1;
	ft_memset(name, ' ', global->fmt->word_max);
	name[global->fmt->word_max] = '\0';
	while (global->file->name[++i])
		name[i] = global->file->name[i];
}

static void			print_name(char *name)
{
	if (global->file->reverse == 1)
		tputs(global->op->reverse_on, 0, my_putchar);
	ft_putchar_fd('[', 1);
	if (global->file->cursor == 1)
		tputs(global->op->under_on, 0, my_putchar);
	ft_putstr_fd(name, 1);
	if (global->file->cursor == 1)
		tputs(global->op->under_off, 0, my_putchar);
	ft_putchar_fd(']', 1);
	if (global->file->reverse == 1)
		tputs(global->op->reverse_off, 0, my_putchar);

}

static void			print_files(void)
{
	int		i;
	int		count;
	char	name[global->fmt->word_max + 1];
	int		exit;

	exit = 1;
	count = 0;
	i = -1;
	while (global->file && exit != 0)
	{
		nb_space(name);
		print_name(name);
		ft_putchar_fd(' ', 1);
		++count;
		if (count == global->fmt->count)
		{
			ft_putchar_fd('\n', 1);
			count = 0;
		}
		global->file = global->file->next;
		if (global->file->first == 1)
			exit = 0;
	}
	if (global->fmt->nbl_save != global->fmt->nb_list)
	{
		while (++i < global->fmt->len_max)
			ft_putchar_fd(' ', 1);
		global->fmt->nbl_save = global->fmt->nb_list;
	}
	if (count != global->fmt->count && count != 0)
		ft_putchar_fd('\n', 1);
}

void				formatting(void)
{
	struct winsize		argp;

	while (global->file && global->file->first != 1)
		global->file = global->file->next;
	ioctl(0, TIOCGWINSZ, &argp);
	nb_list();
	global->fmt->count = argp.ws_col / global->fmt->len_max;
	if (global->fmt->count == 0)
	{
		ft_putendl_fd("Enlarge the window.", 2);
		return ;
	}
	global->fmt->row = global->fmt->nb_list / global->fmt->count;
	if (global->fmt->row + 1 >= argp.ws_row)
	{
		ft_putendl_fd("Enlarge the window.", 2);
		return ;
	}
	if (global->fmt->nb_list % global->fmt->count)
		++global->fmt->row;
	print_files();
}
