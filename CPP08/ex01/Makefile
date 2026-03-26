
CPP      := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++98
NAME     := span

SRC := main.cpp span.cpp
OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) span.hpp
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

%.o: %.cpp span.hpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
