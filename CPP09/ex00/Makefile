# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/25 21:36:17 by anacaro5          #+#    #+#              #
#    Updated: 2026/03/25 21:36:18 by anacaro5         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = btc
FLAGS = -Wall -Werror -Wextra -g3 -std=c++98
CC = c++

# Colors Definition
BLUE = "\033[34;1m"
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths for libraries
BIN_PATH = ./bin/
MANDATORY_SOURCES_PATH = ./
INCLUDES_PATH = ./includes/

SRC = \
	main.cpp BitcoinExchange.cpp

OBJECTS = $(addprefix $(BIN_PATH), $(SRC:%.cpp=%.o))

all: $(BIN_PATH) $(NAME)

$(BIN_PATH)%.o: $(MANDATORY_SOURCES_PATH)%.cpp
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES_PATH)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

clean:
	@rm -rf $(BIN_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re bonus