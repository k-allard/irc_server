NAME = ircserv

SRCS = sources/Channel.cpp sources/Server.cpp sources/Client.cpp sources/Cmds.cpp sources/Parser.cpp  sources/main.cpp\
sources/MessageCommand.cpp sources/Message.cpp sources/MessageParams.cpp sources/MessagePrefix.cpp

CC = clang++

OBJS = $(SRCS:.cpp=.o)

HEADER = header.hpp

INCLUDES= -I ./includes

FLAGS2 =-g -fsanitize=address
FLAGS = -std=c++98 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Preparing ircserv.net. . ."
	$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(INCLUDES)
	@echo "ircserv.net is ready!"
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
