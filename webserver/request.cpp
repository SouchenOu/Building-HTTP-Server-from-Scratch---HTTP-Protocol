/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:36:06 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:36:08 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/headers.hpp"


// constructers


Request::Request()
{
    std::cout << "Send a request\n";
}

Request::Request(const std::string buffer)
{
  
	vector<string> request_Headers = ft_divise(buffer, "\r\n");
    vector<string>::iterator iter = request_Headers.begin();
    while(iter != request_Headers.end());
    {
        vector<string> First_line = ft_divise(*iter, ": ");
        if(First_line.size() < 2)
        {
            std::cout << "Error-->should have at least 1 argument\n";
            //break ;
        }
    }
	
}

// // destructer
Request::~Request()
{

}