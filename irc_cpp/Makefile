NAME = ircserv

SRCS = sources/*.cpp

OBJS = $(SRCS:.cpp=.o)

HEADER = header.hpp

FLAGS2 =-Wall -Wextra -Werror
FLAGS =-g -fsanitize=address -std=c++98

all: $(NAME)

$(NAME):
	@echo "\x1b[33m Preparing $(NAME)...\x1b[0m"
	@clang++ -o $(NAME) $(SRCS) $(FLAGS)
	@echo "\x1b[32m $(NAME) are ready!\x1b[0m"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test: re
	@./ircserv 6667 123

test2: re
	@./ircserv 6668 123

%.o: %.cpp
	@clang++ $(FLAGS) -c $< -o $@

.PHONY:	all clean fclean re