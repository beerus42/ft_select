/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 03:13:06 by liton             #+#    #+#             */
/*   Updated: 2017/09/14 18:06:07 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		sig_op(int sig)
{
	if (sig == SIGWINCH)
		tputs(tgetstr("cl", NULL), 0, my_putchar);
}

void			ft_signal(void)
{
	signal(28, sig_op);
}
