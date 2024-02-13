# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 19:57:48 by lvichi            #+#    #+#              #
#    Updated: 2024/02/13 16:21:37 by lvichi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread #-fsanitize=address
RM = rm -fr
FILES = *.c
OBJS = obj_bonus/*.o
OBJS_FOLDER = obj_bonus/

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(FILES)
	@mkdir -p $(OBJS_FOLDER)
	@$(CC) $(CFLAGS) -c $(FILES)
	@mv *.o $(OBJS_FOLDER)

clean:
	@$(RM) $(OBJS) $(OBJS_FOLDER)

fclean:
	@$(RM) $(OBJS) $(NAME) $(OBJS_FOLDER)

re: fclean all
