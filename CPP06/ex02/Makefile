# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 17:57:16 by anacaro5          #+#    #+#              #
#    Updated: 2025/10/08 17:57:18 by anacaro5         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP      := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++98
NAME     := identify

SRC := main.cpp Base.cpp
OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) Base.hpp
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

%.o: %.cpp Base.hpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

