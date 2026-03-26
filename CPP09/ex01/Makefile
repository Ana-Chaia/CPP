# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/25 11:34:27 by anacaro5          #+#    #+#              #
#    Updated: 2026/03/25 11:34:29 by anacaro5         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN
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
	main.cpp RPN.cpp

OBJECTS = $(addprefix $(BIN_PATH), $(SRC:%.cpp=%.o))

all: $(BIN_PATH) $(NAME)

$(BIN_PATH)%.o: $(MANDATORY_SOURCES_PATH)%.cpp
	@echo $(BLUE)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))$(COLOR_LIMITER)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES_PATH)
	@echo " "

$(NAME): $(OBJECTS)
	@echo $(CYAN)"--------------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"|      executable was created successfully!!     |"$(COLOR_LIMITER)
	@echo $(CYAN)"--------------------------------------------------"$(COLOR_LIMITER)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)
	@echo " "

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	@rm -rf $(BIN_PATH)

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@rm -rf $(NAME)

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re bonus