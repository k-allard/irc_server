NAME = ircserv

SRCS = sources/Channel.cpp sources/Server.cpp sources/Client.cpp sources/Cmds.cpp sources/Parser.cpp  sources/main.cpp\
sources/MessageCommand.cpp sources/Message.cpp sources/MessageParams.cpp sources/MessagePrefix.cpp

CC = clang++

OBJS = $(SRCS:.cpp=.o)

HEADER = header.hpp

INCLUDES= -I ./includes

FLAGS2 =-Wall -Wextra -Werror
FLAGS =-g -fsanitize=address -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\x1b[33mPreparing ircserv.net. . .\x1b[0m"
	@$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(INCLUDES)
	@echo "\x1b[32mircserv.net is ready!\x1b[0m"
	@echo "Usage: ./ircserv <port> <password>"

%.o: %.cpp
	@$(CC) $(FLAGS) $(INCLUDES) -c $^ -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test: re
	./ircserv 6667 123

test2: re
	./ircserv 6668 123

.PHONY:	all clean fclean re
