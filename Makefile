# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 15:58:32 by bel-barb          #+#    #+#              #
#    Updated: 2024/03/28 12:36:06 by bel-barb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client
NAME2 = server

NAME_BONUS = client_bonus
NAME2_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCEC = client.c helpers/ft_atoi.c helpers/ft_strlen.c helpers/ft_printf.c helpers/print_num.c helpers/print_str.c helpers/print_hex.c helpers/print_char.c
SOURCES = server.c helpers/ft_atoi.c helpers/ft_strlen.c helpers/ft_printf.c helpers/print_num.c helpers/print_str.c helpers/print_hex.c helpers/print_char.c
SOURCEC_BNS = client_bonus.c helpers/ft_atoi.c helpers/ft_strlen.c helpers/ft_printf.c helpers/print_num.c helpers/print_str.c helpers/print_hex.c helpers/print_char.c
SOURCES_BNS = server_bonus.c helpers/ft_atoi.c helpers/ft_strlen.c helpers/ft_printf.c helpers/print_num.c helpers/print_str.c helpers/print_hex.c helpers/print_char.c

all: $(NAME2) $(NAME)

$(NAME2): $(SOURCES) minitalk.h helpers/ft_printf.h
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

$(NAME): $(SOURCEC) minitalk.h helpers/ft_printf.h
	$(CC) $(CFLAGS) -o $@ $(SOURCEC)

$(NAME2_BONUS): $(SOURCES_BNS) minitalk.h helpers/ft_printf.h
	$(CC) $(CFLAGS) -o $@ $(SOURCES_BNS)

$(NAME_BONUS): $(SOURCEC_BNS) minitalk.h helpers/ft_printf.h
	$(CC) $(CFLAGS) -o $@ $(SOURCEC_BNS)

clean:
	rm -f server client
	rm -f server_bonus client_bonus
	
fclean: clean
	rm -f server client
	rm -f server_bonus client_bonus

re: fclean all

bonus: $(NAME_BONUS) $(NAME2_BONUS)

.PHONY: all clean fclean re