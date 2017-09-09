/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:57:43 by liton             #+#    #+#             */
/*   Updated: 2017/09/09 22:00:59 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			nb_list(t_files *file, t_format *fmt)
{
	int		exit;

	exit = 1;
	fmt->nb_list = 0;
	while (file && exit != 0)
	{
		++fmt->nb_list;
		file = file->next;
		if (file->first == 1)
			exit = 0;
	}
}

static void			nb_space(t_files *file, t_format *fmt, char *name)
{
	int		i;

	i = -1;
	ft_memset(name, ' ', fmt->word_max);
	name[fmt->word_max] = '\0';
	while (file->name[++i])
		name[i] = file->name[i];
}

static void			print_name(char *name, t_files *file, t_op *op)
{
	if (file->reverse == 1)
		tputs(op->reverse_on, 0, my_putchar);
	ft_putchar_fd('[', 1);
	if (file->cursor == 1)
		tputs(op->under_on, 0, my_putchar);
	ft_putstr_fd(name, 1);
	if (file->cursor == 1)
		tputs(op->under_off, 0, my_putchar);
	ft_putchar_fd(']', 1);
	if (file->reverse == 1)
		tputs(op->reverse_off, 0, my_putchar);

}

static void			print_files(t_files *file, t_format *fmt, t_op *op)
{
	int		i;
	int		count;
	char	name[fmt->word_max + 1];
	int		exit;

	exit = 1;
	count = 0;
	i = -1;
	while (file && exit != 0)
	{
		nb_space(file, fmt, name);
		print_name(name, file, op);
		ft_putchar_fd(' ', 1);
		++count;
		if (count == fmt->count)
		{
			ft_putchar_fd('\n', 1);
			count = 0;
		}
		file = file->next;
		if (file->first == 1)
			exit = 0;
	}
	if (fmt->nbl_save != fmt->nb_list)
	{
		while (++i < fmt->len_max)
			ft_putchar_fd(' ', 1);
		fmt->nbl_save = fmt->nb_list;
	}
	if (count != fmt->count && count != 0)
		ft_putchar_fd('\n', 1);
}

int					formatting(t_files *file, t_op *op, t_format *fmt)
{
	struct winsize		argp;

	ioctl(1, TIOCGWINSZ, &argp);
	nb_list(file, fmt);
	fmt->count = argp.ws_col / fmt->len_max;
	fmt->row = fmt->nb_list / fmt->count;
	if (fmt->nb_list % fmt->count)
		++fmt->row;
	print_files(file, fmt, op);
	return (fmt->count);
}
