/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liton <livbrandon@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 23:05:55 by liton             #+#    #+#             */
/*   Updated: 2017/09/08 02:17:01 by liton            ###   ########.fr       */
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

typedef struct		s_files
{
	int				first;
	char			*name;
	struct s_files	*prev;
	struct s_files	*next;
}					t_files;

typedef struct		s_format
{
	int				row;
	int				count;
	int				nb_list;
	int				save;
	int				len_max;
}					t_format;

void				formatting(t_files *file);

#endif
