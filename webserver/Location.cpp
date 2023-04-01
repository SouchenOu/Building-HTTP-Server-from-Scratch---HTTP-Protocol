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

#include "../headers/Location.hpp"



Location::Location()
{

}

Location::~Location()
{

}
// getters

string Location::get_root()
{
    return root;
}

string Location::get_try_files()
{
    return try_files;
}

string Location::get_return_line()
{
    return return_line;
}

string Location::get_alias()
{
    return alias;
}

int Location::get_http_redirection()
{
    return http_redirection;
}

string Location::get_autoindex()
{
    return autoindex;
}

// setters

void Location::set_root(string root)
{
    this->root = root;
}

void Location::set_return_line(string return_line)
{
    this->return_line = return_line;
}
void Location::set_alias(string alias)
{
    this->alias = alias;
}
void Location::set_try_files(string try_files)
{
    this->try_files = try_files;
}

void Location::set_http_redirection(int http_redirection)
{
    this->http_redirection = http_redirection;
}

void Location::set_autoindex(string autoindex)
{
    this->autoindex = autoindex;
}




