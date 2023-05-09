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

FILES =  webserver/it_is_dir_or_file.cpp webserver/Location.cpp  webserver/parce_config_file.cpp webserver/server.cpp webserver/binding_socket.cpp webserver/webserver.cpp webserver/main.cpp webserver/WebBrowser.cpp webserver/request.cpp webserver/response.cpp

INC =  headers/Location.hpp headers/request.hpp headers/server.hpp headers/binding_socket.hpp headers/webserver.hpp headers/WebBrowser.hpp headers/request.hpp headers/response.hpp headers/tools.hpp


FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(FILES) $(INC)
	c++ $(FLAGS) $(FILES) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re