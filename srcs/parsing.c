/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 18:37:19 by liton             #+#    #+#             */
/*   Updated: 2017/09/16 20:21:28 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				right(void)
{
	global->file->cursor = 0;
	global->file = global->file->next;
	global->file->cursor = 1;
}

void				left(void)
{
	global->file->cursor = 0;
	global->file = global->file->prev;
	global->file->cursor = 1;
}

void				delete_file(t_files **file)
{
	if ((*file)->first == 1)
	{
		if ((*file)->next->first == 1)
		{
			ft_strdel(&global->file->name);
			free(global->file);
			free(global->fmt);
			free(global->op);
			shell_off();
			exit(EXIT_SUCCESS);
		}
		(*file)->next->first = 1;
	}
	(*file)->prev->next = (*file)->next;
	(*file)->next->prev = (*file)->prev;
	ft_strdel(&(*file)->name);
	free(*file);
	file = NULL;
}

static t_files		*create_files(t_files *file, char *name)
{
	t_files		*new;

	if (!(new = (t_files*)malloc(sizeof(t_files))))
		return (NULL);
	if (file == NULL)
	{
		new->name = ft_strdup(name);
		new->first = 1;
		new->reverse = 0;
		new->cursor = 1;
	}
	else
	{
		new->first = 0;
		new->cursor = 0;
		new->reverse = 0;
		new->name = ft_strdup(name);
		new->prev = file;
		new->prev->next = new;
	}
	return (new);
}

t_files				*parsing(char **av)
{
	int			i;
	t_files		*file;
	t_files		*first;

	i = 0;
	file = NULL;
	while (av[++i])
	{
		file = create_files(file, av[i]);
		if (i == 1)
			first = file;
	}
	file->next = first;
	first->prev = file;
	file = file->next;
	return (file);
}
