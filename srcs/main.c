/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 22:47:04 by liton             #+#    #+#             */
/*   Updated: 2017/09/08 03:09:58 by liton            ###   ########.fr       */
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

int		shell_off(void)
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

t_files		*create_files(t_files *file, char *name)
{
	t_files		*new;

	if (!(new = (t_files*)malloc(sizeof(t_files))))
		return (NULL);
	if (file == NULL)
	{
		new->name = ft_strdup(name);
		new->first = 1;
	}
	else
	{
		new->first = 0;
		new->name = ft_strdup(name);
		new->prev = file;
		new->prev->next = new;
	}
	return (new);
}

t_files		*parsing(char **av)
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

int			my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_files				*file;
	char				*term_name;
	char				*res;

	(void)av;
	(void)env;
	if (ac < 2 || (term_name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, term_name) <= 0)
		return (-1);
	file = parsing(av);
	if ((res = tgetstr("cl", NULL)) == NULL)
    	return (-1);
	tputs(res, 0, my_putchar);
	formatting(file);
}
