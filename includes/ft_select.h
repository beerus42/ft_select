/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 23:05:55 by liton             #+#    #+#             */
/*   Updated: 2017/09/14 21:50:42 by liton            ###   ########.fr       */
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

typedef struct		s_global
{
	struct s_files   *file;
	struct s_format  *fmt;
	struct s_op		 *op;
}					t_global;

struct s_global		*global;

void				formatting(void);
t_files				*parsing(char **av);
void				read_buff(void);
void				delete_file(t_files **file);
t_format			*name_size(t_files *file);
void				ft_signal(void);

#endif
