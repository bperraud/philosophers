# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 23:06:59 by bperraud          #+#    #+#              #
#    Updated: 2022/06/16 23:06:59 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			    = main.c philo.c utils.c init.c

SDIR			= src
HDIR			= include
ODIR			= objs

OBJ	  			= $(addprefix $(ODIR)/, $(SRC:.c=.o))

CC				= gcc
#CFLAGS			= -Wall -Wextra -Werror -Iinclude
CFLAGS			= -Iinclude
RM				= rm -f

NAME			= philo

all:			 tmp $(NAME)

$(NAME): 		$(OBJ)
				$(CC) $(OBJ) -pthread -o $(NAME)

$(ODIR)/%.o: 	$(SDIR)/%.c
				$(CC) $(CFLAGS)  -c $< -o $@

tmp:
				mkdir -p objs

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
