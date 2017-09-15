/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 03:13:06 by liton             #+#    #+#             */
/*   Updated: 2017/09/15 04:11:45 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		sig_op(int sig)
{
	if (sig == SIGWINCH)
	{
		tputs(global->op->clear, 0, my_putchar);
		formatting();
	}
	if (sig == SIGQUIT || sig == SIGINT || sig == SIGKILL || sig == SIGTERM)
	{
		shell_off();
		exit(EXIT_SUCCESS);	
	}
}

void			ft_signal(void)
{
	int		i;

	i = 0;
	while (++i < 32)
		signal(i, sig_op);
}
