/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 22:47:04 by liton             #+#    #+#             */
/*   Updated: 2017/09/09 21:56:18 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		shell_on(void)
{
	struct termios term;
 
	if (tcgetattr(0, &term) == -1)
  	 return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
	   return (-1);
	return (0);
}

static int		shell_off(void)
{
	struct termios		term;

	if (tcgetattr(0, &term) == -1)
     return (-1);
	term.c_lflag &= ~(ICANON); 
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return(0);
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

static void		ft_select(t_files *file, t_op *op, t_format *fmt)
{
	int			count;
	t_files		*begin;

	begin = file;
	tputs(op->clear, 0, my_putchar);
	while (42)
	{
		tputs(tgoto(op->cm, 0, 0), 0, my_putchar);
		count = formatting(begin, op, fmt);
		read_buff(&file, &begin, count);
	}
}

int				main(int ac, char **av, char **env)
{
	t_format			*fmt;
	t_files				*file;
	char				*term_name;
	t_op				*op;

	(void)av;
	(void)env;
	if (!*env ||ac < 2 || (term_name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, term_name) <= 0)
		return (-1);
	if ((op = init_op()) == NULL)
		return (-1);
	file = parsing(av);
	fmt = name_size(file);
	shell_off();
	ft_select(file, op, fmt);
}
