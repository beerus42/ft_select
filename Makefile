# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: liton <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/14 20:24:52 by liton             #+#    #+#              #
#*   Updated: 2017/09/10 04:45:09 by liton            ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME    = 	ft_select
CC      = 	gcc
LFLAGS  = 	-ltermcap
FLAGS   = 	-Wall -Wextra -Werror
LIB     = 	libft/libft.a
HEADER  = 	includes/
LIBSRC  = 	libft/
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC	=		formatting.c		\
			parsing.c			\
			read.c				\
			name_size.c      	\
			signal.c			\
			main.c
# colors
GRN     =   \033[0;32m
RED     =   \033[0;31m
CYN     =   \033[0;36m
NC      =   \033[0m
SRCS        = $(addprefix $(SRCDIR), $(SRC))
OBJS        = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) $(LFLAGS) -L./$(LIBSRC) -lft -o $(NAME) $(OBJS)
	@echo "\n${CYN}PROCESSING DONE !${NC}"

$(OBJDIR):
	@mkdir -p objs

$(LIB):
	@echo "${CYN}Processing ${NC}./libft/objs ${CYN}[${NC}...${CYN}]${NC}"
	@make -C $(LIBSRC)
	@echo "\n${CYN}Processing ${NC}./objs ${CYN}[${NC}...${CYN}]${NC}"

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)$(NAME).h
	@echo "${GRN}Compiling${NC} $@"
	@$(CC) $(FLAGS) -c -o $@ $< -I $(HEADER)

clean:
	@echo "${RED}Cleaning ${NC}./objs/ ${RED}[${NC}...${RED}]${NC}"
	@rm -rf $(OBJS)
	@echo "${RED}Cleaning ${NC}./libft/objs/ ${RED}[${NC}...${RED}]${NC}"
	@make -C $(LIBSRC) clean

fclean: clean
	@echo "${RED}Cleaning ${NC}./${RED}ft_ls${NC}"
	@rm -Rf $(NAME)
	@echo "${RED}Cleaning ${NC}./libft/${RED}libft.h${NC}\n"
	@make -C $(LIBSRC) fclean
	@echo "${RED}DELET DONE !${NC}"

re: fclean all

.PHONY: all clean fclean re
