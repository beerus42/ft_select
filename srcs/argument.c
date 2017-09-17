/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 18:54:31 by liton             #+#    #+#             */
/*   Updated: 2017/09/17 03:05:18 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				support_formatting(int count)
{
	int		i;

	i = -1;
	if (global->fmt->nbl_save != global->fmt->nb_list)
	{
		while (++i < global->fmt->len_max)
			ft_putchar_fd(' ', 2);
		global->fmt->nbl_save = global->fmt->nb_list;
	}
	if (count != global->fmt->count && count != 0)
		ft_putchar_fd('\n', 2);
}

void				free_struct(void)
{
	t_files		*tmp;

	while (global->file && global->file->first != 1)
		global->file = global->file->next;
	global->file = global->file->next;
	while (global->file->first == 0)
	{
		tmp = global->file;
		global->file = global->file->next;
		ft_strdel(&tmp->name);
		free(tmp);
		tmp = NULL;
	}
	ft_strdel(&global->file->name);
	free(global->file);
	global->file = NULL;
	free(global->fmt);
	free(global->op);
	free(global);
}

static char			*argument(void)
{
	char	*arg;
	int		exit;

	exit = 1;
	arg = ft_strnew(0);
	while (global->file && global->file->first != 1)
		global->file = global->file->next;
	while (exit)
	{
		if (global->file->reverse == 1)
		{
			arg = ft_strjoinfree(arg, global->file->name, 1);
			arg = ft_strjoinfree(arg, " ", 1);
		}
		global->file = global->file->next;
		if (global->file->first == 1)
			exit = 0;
	}
	if (arg[0] != '\0')
		arg[ft_strlen(arg) - 1] = '\0';
	return (arg);
}

void				enter(void)
{
	char	*arg;

	arg = argument();
	shell_off();
	if (arg[0] != '\0')
		ft_putendl_fd(arg, 1);
	ft_strdel(&arg);
	free_struct();
	exit(0);
}
