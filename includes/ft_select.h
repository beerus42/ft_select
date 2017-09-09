/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 23:05:55 by liton             #+#    #+#             */
/*   Updated: 2017/09/09 22:01:13 by liton            ###   ########.fr       */
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
	char			*cm;
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
	int				row;
	int				count;
	int				nb_list;
	int				nbl_save;
	int				len_max;
	int				word_max;
}					t_format;

int					formatting(t_files *file, t_op *op, t_format *fmt);
int					my_putchar(int c);
t_files				*parsing(char **av);
void				read_buff(t_files **file, t_files **begin, int count);
void				delete_file(t_files **file, t_files **begin);
t_format			*name_size(t_files *file);

#endif
