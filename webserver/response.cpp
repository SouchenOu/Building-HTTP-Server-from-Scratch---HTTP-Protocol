/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:36:12 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:36:13 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/response.hpp"

#include "../headers/headers.hpp"

response::response()
{
		std::cout << "response\n";
}


response::~response()
{

}


void response::response_preparation(const std::set<server*> &servers, std::map<std::string, std::string> headers)
{
	string Host;
	if(headers.find("Host") != headers.end())
	{
		Host = headers.find("host")->second;
	}
}

