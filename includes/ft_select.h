/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 23:05:55 by liton             #+#    #+#             */
/*   Updated: 2017/09/09 03:56:19 by liton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include "../libft/libft.h"
# include <sys/ioctl.h>

typedef struct		s_op
{
	char			*reverse_on;
	char			*reverse_off;
	char			*clear;
	char			*under_on;
	char			*under_off;
}					t_op;

typedef struct		s_files
{
	int				first;
	char			*name;
	int				cursor;
	int				reverse;
	struct s_files	*prev;
	struct s_files	*next;
}					t_files;

typedef struct		s_format
{
	int				color;
	int				row;
	int				count;
	int				nb_list;
	int				len_max;
}					t_format;

void				formatting(t_files *file, t_op *op);
int					my_putchar(int c);
t_files				*parsing(char **av);
void				read_buff(t_files **file, t_files **begin);
void				delete_file(t_files **file, t_files **begin);

#endif
