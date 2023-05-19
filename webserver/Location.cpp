/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:30:21 by souchen           #+#    #+#             */
/*   Updated: 2023/03/28 19:30:23 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/location.hpp"



Location::Location()
{

    http_redirection = 0;
    upload_enable = 0;
}

Location::~Location()
{
   
}
// getters

std::string Location::get_root()
{
    return root;
}


std::string Location::get_return_line()
{
    return return_line;
}



int Location::get_http_redirection()
{
    return http_redirection;
}



std::string Location::get_autoindex()
{
    return autoindex;
}
int Location::get_upload_enable()
{
    return upload_enable;
}

std::string Location::get_index()
{
    return index;
}

std::string Location::get_path()
{
    return path;
}

std::vector<std::string>	Location::get_http_allow_method()
{
	return (this->http_allow_method);
}

// setters
void Location::set_root(std::string root)
{
    this->root = root;
}

void Location::set_return_line(std::string return_line)
{
    this->return_line = return_line;
}


void Location::set_http_redirection(int http_redirection)
{
    this->http_redirection = http_redirection;
}

void Location::set_autoindex(std::string autoindex)
{
    this->autoindex = autoindex;
}

void Location::set_upload_enable(int upload_enable)
{
    this->upload_enable = upload_enable;
}


void Location::set_index(std::string index)
{
    this->index = index;
}

void Location::set_path(std::string Path)
{
    this->path = Path;
}

void Location::push_allow_HTTP_methods(std::string http_method_allow)
{
    http_allow_method.push_back(http_method_allow);
}




