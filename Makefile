# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souchen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 15:17:25 by souchen           #+#    #+#              #
#    Updated: 2023/03/19 15:17:26 by souchen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = WebServ

FILES =  sockets/binding_socket.cpp sockets/connecting.cpp  sockets/listening.cpp sockets/SocketSimple.cpp  server/request.cpp server/server.cpp server/test.cpp server/mainServer.cpp

INC =  sockets/binding_socket.hpp sockets/connecting.hpp  sockets/listening.hpp sockets/SocketSimple.hpp server/server.hpp server/test.hpp


FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(FILES) $(INC)
	c++ $(FLAGS) $(FILES) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re