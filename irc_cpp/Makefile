NAME = ircserv

SRCS =	sources/Channel.cpp \
		sources/Client.cpp \
		sources/Cmds.cpp \
		sources/main.cpp \
		sources/Message.cpp \
		sources/MessageCommand.cpp \
		sources/MessageParams.cpp \
		sources/MessagePrefix.cpp \
		sources/Parser.cpp \
		sources/Server.cpp

OBJS =	$(SRCS:.cpp=.o)

HEADER =	header.hpp

FLAGS2 =-g -fsanitize=address
FLAGS =-std=c++98 -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "\x1b[33mPreparing ircserv.net. . .\x1b[0m"
	clang++ -o $(NAME) $(SRCS) $(FLAGS)
	@echo "\x1b[32mircserv.net is ready!\x1b[0m"
	@echo "Usage: ./ircserv <port> <password>"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test: re
	./ircserv 6667 123

test2: re
	./ircserv 6668 123

%.o: %.cpp
	@clang++ $(FLAGS) -c $< -o $@

.PHONY:	all clean fclean re
