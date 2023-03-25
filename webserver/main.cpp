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

#include "../headers/server.hpp"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Error: We need a config file!\n";
        return -1;
    }
    else if(argc == 2)
    {
        	ifstream FileToCheck(argv[1]);
		    if (!FileToCheck.is_open())
		    {
			    std::cout << "Error: File is empty" << std::endl;
			    return -1;
		    }
		    FileToCheck.close();
    }

    parse_config_file(argv[1]);
    Webserver webserver;

	return 0;
    
}