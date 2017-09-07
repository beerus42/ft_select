/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 01:09:49 by liton             #+#    #+#             */
/*   Updated: 2017/09/07 02:32:44 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include "libft/libft.h"

int		my_putchar(int c)
{
	write(1, &c, 1);
	return(0);
}

int     voir_touche()
{
  char     buffer[3];
 
    read(0, buffer, 3);
	if (buffer[2] == 65)
		printf("Fleche haut\n");
	if (buffer[2] == 66)
		printf("Fleche bas\n");
	if (buffer[2] == 68)
		printf("Fleche gauche\n");
	if (buffer[2] == 67)
		tputs(tgetstr("cl", NULL), 1, &my_putchar);
  return (0);
}



int              main(int ac, char **av, char **env)
{
//	char				buffer[3 + 1];
	char				*res;
  	char           		*name_term;
 	struct termios 		term;
 	int		i = 0;
	(void)env;
	(void)ac;
	(void)av;
  if ((name_term = getenv("TERM")) == NULL)
     return (-1);
  if (tgetent(NULL, name_term) != 1)
     return (-1);
//   remplis la structure termios des possibilités du terminal.
  if (tcgetattr(0, &term) == -1)
	    return (-1);
	term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	// On applique les changements :
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	res = tgetstr("Xh", NULL);
	while (42)
	{
		i = 0;
		tputs(tgetstr("cl", NULL), 1, &my_putchar);
		tputs(res, 1, &my_putchar);
		while(av[i])
			ft_putendl_fd(av[i++], 1);
		sleep(5);
		voir_touche();
	}
}

