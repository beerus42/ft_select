/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:57:43 by liton             #+#    #+#             */
/*   Updated: 2017/09/08 03:09:13 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			name_size_max(t_files *file, t_format *fmt)
{
	int		save;
	int		exit;

	exit = 1;
	save = 0;
	fmt->save = 0;
	fmt->count = 0;
	fmt->row = 0;
	fmt->nb_list = 0;
	fmt->len_max = 0;
	while (file && exit != 0)
	{
		++fmt->nb_list;
		if ((save = ft_strlen(file->name)) > fmt->len_max)
			fmt->len_max = save;
		file = file->next;
		if (file->first == 1)
			exit = 0;
	}
	fmt->save = fmt->len_max;
	++fmt->len_max;
}

static void			my_strcpy(char *dest, char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
}

static void			nb_space(t_files *file, t_format *fmt, char *name)
{
	ft_memset(name, ' ', fmt->save);
	name[fmt->save] = '\0';
	my_strcpy(name, file->name);
}

static void			print_files(t_files *file, t_format *fmt)
{
	int		count;
	char	name[fmt->save + 1];
	int		exit;

	exit = 1;
	count = 0;
	while (file && exit != 0)
	{
		nb_space(file, fmt, name);
		ft_putstr_fd(name, 1);
		ft_putchar_fd(' ', 1);
		count++;
		if (count == fmt->count)
		{
			ft_putchar_fd('\n', 1);
			count = 0;
		}
		file = file->next;
		if (file->first == 1)
			exit = 0;
	}
	if (count != fmt->count && count != 0)
		ft_putchar('\n');
}

void				formatting(t_files *file)
{
	t_format			*fmt;
	struct winsize		argp;

	fmt = NULL;
	if (!(fmt = (t_format*)malloc(sizeof(t_format))))
		return ;
	name_size_max(file, fmt);
	ioctl(1, TIOCGWINSZ, &argp);
	fmt->count = argp.ws_col / fmt->len_max;
	fmt->row = fmt->nb_list / fmt->count;
	if (fmt->nb_list % fmt->count)
		++fmt->row;
	print_files(file, fmt);
	free(fmt);
}
