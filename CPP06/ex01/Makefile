# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 17:56:00 by anacaro5          #+#    #+#              #
#    Updated: 2025/10/08 17:57:36 by anacaro5         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP      := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++98
NAME     := serializer

SRC      := main.cpp serializer.cpp
OBJ      := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

