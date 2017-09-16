/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 03:13:06 by liton             #+#    #+#             */
/*   Updated: 2017/09/16 04:38:42 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int             shell_off(void)
{
	if (tcsetattr(0, TCSADRAIN, &global->term) == -1)
		return (-1);
	if (tputs(tgetstr("vs", NULL), 0, my_putchar) == ERR)
		return (-1);
	if (tputs(tgetstr("te", NULL), 0, my_putchar) == ERR)
		return (-1);
	return (0);
}

int             shell_on(void)
{
	struct termios          term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	if (tputs(tgetstr("ti", NULL), 0, my_putchar) == ERR)
		return (-1);
	if (tputs(tgetstr("vi", NULL), 0, my_putchar) == ERR)
		return (-1);
	return(0);
}

void		sig_op(int sig)
{
	if (sig == SIGWINCH)
	{
		tputs(global->op->clear, 0, my_putchar);
		formatting();
	}
	else if (sig == SIGQUIT || sig == SIGINT || sig == SIGKILL || sig == SIGTERM)
	{
		shell_off();
		exit(EXIT_SUCCESS);	
	}
	else if (sig == SIGTSTP || sig == SIGSTOP)
	{
		char	susp[2];

		susp[0] = global->term.c_cc[VSUSP];
		susp[1] = 0;
		shell_off();
		signal(SIGTSTP, SIG_DFL);		
		ioctl(0, TIOCSTI, susp);
	}
	else if (sig == SIGCONT)
	{
		shell_on();
		signal(SIGTSTP, sig_op);		
		signal(SIGCONT, sig_op);	
		tputs(global->op->clear, 0, my_putchar);
		formatting();
	}
}

void			ft_signal(void)
{
	signal(2, sig_op);
	signal(3, sig_op);
	signal(9, sig_op);
	signal(15, sig_op);
	signal(17, sig_op);
	signal(18, sig_op);
	signal(19, sig_op);
	signal(28, sig_op);
}
