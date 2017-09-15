/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 22:47:04 by liton             #+#    #+#             */
/*   Updated: 2017/09/16 01:38:40 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_format        *name_size(void)
{
        int                             save;
        int                             exit;
        t_format                *fmt;

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
                if ((save = ft_strlen(global->file->name)) > fmt->len_max)
                        fmt->len_max = save;
                global->file = global->file->next;
                if (global->file->first == 1)
                        exit = 0;
        }
        fmt->word_max = fmt->len_max;
        fmt->len_max += 3;
        return (fmt);
}

static t_op		*init_op(void)
{
	t_op	*op;

	if (!(op = (t_op*)malloc(sizeof(t_op))))
		return (NULL);
	if ((op->clear = tgetstr("cl", NULL)) == NULL)
		return (NULL);
	if ((op->under_on = tgetstr("us", NULL)) == NULL)
		return (NULL);
	if ((op->under_off = tgetstr("ue", NULL)) == NULL)
		return (NULL);
	if ((op->reverse_on = tgetstr("mr", NULL)) == NULL)
		return (NULL);
	if ((op->reverse_off = tgetstr("me", NULL)) == NULL)
		return (NULL);
	if ((op->cm = tgetstr("cm", NULL)) == NULL)
		return (NULL);
	return (op);
}

static void		ft_select(void)
{
	tputs(global->op->clear, 0, my_putchar);
	while (42)
	{
		tputs(tgoto(global->op->cm, 0, 0), 0, my_putchar);
		formatting();
		read_buff();
	}
}

int				main(int ac, char **av, char **env)
{
	char				*term_name;

	if (!(global = (t_global*)malloc(sizeof(t_global))))
		return (-1);
	if (!*env || ac < 2 || (term_name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, term_name) <= 0 || (global->op = init_op()) == NULL)
		return (-1);
	if (tcgetattr(0, &global->term) == -1)
		return (-1);
	global->file = parsing(av);
	global->fmt = name_size();
	shell_on();
	ft_signal();
	ft_select();
}
