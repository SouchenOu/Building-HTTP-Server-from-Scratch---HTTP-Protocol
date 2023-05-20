/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserver.hpp"
#include "../headers/server.hpp"
#include <signal.h>

//Developpe a webserv like NGINX

/*****One of its many impressive features is that it can serve static content (media files, HTML) efficiently.*/
// CGI : Common Gateway Interface --> is an interface type for web servers to execute apps that execute like console applications running on a server that generates web pages in dynamical way

/*****CGI program will reside in a special directory ( with limited rights ) in order to let the web server to understand that the file is for execution only and not to display in the user’s browser.*/


int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    if(argc != 2)
    {
        std::cout << YELLOW << "Add default config file!\n";
        std::ifstream FileToCheck("config_file/config_file-default.conf");
		    if (!FileToCheck.is_open())
		    {
			    std::cout << RED << "Error: opening file--> This file doesnt exist" << std::endl;
			    return -1;
		    }
		    FileToCheck.close();
        Webserver webserver;
        webserver.parcing_config_file("config_file/config_file-default.conf");
        webserver.Establish_connection();
    }
    else if(argc == 2)
    {
        //This data type represents the input file stream and is used to read information from files.
        	std::ifstream FileToCheck(argv[1]);
		    if (!FileToCheck.is_open())
		    {
			    std::cout << RED << "Error: opening file--> This file doesnt exist" << std::endl;
			    return -1;
		    }
		    FileToCheck.close();
        Webserver webserver;
        webserver.parcing_config_file(argv[1]);
        webserver.Establish_connection();
    }
   

    

	return 0;
    
}