# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 13:06:27 by aobshatk          #+#    #+#              #
#    Updated: 2025/10/30 00:39:01 by aobshatk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP = c++
CPPFLAGS = -std=c++98 -Wall -Wextra -Werror -g

CPPFILES = BitcoinExchange.cpp 

NAME = btc

all: $(NAME)

$(NAME):
	$(CPP) $(CPPFLAGS) $(CPPFILES) main.cpp -o $(NAME)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re