# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 19:57:48 by lvichi            #+#    #+#              #
#    Updated: 2024/01/30 23:48:49 by lvichi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
RM = rm -fr
FILES = *.c
OBJS = obj/*.o

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(FILES)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $(FILES)
	@mv *.o obj/

clean:
	@$(RM) $(OBJS) obj

fclean:
	@$(RM) $(OBJS) $(NAME) obj

re: fclean all
