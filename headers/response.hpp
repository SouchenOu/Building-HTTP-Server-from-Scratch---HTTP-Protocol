/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:35:57 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:35:59 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../headers/tools.hpp"

class server;
class Location;
class response
{
  
    public:

        //constructers
        response();
        //~destructer
        ~response();

        //used function

        std::string response_header(int size_of_file, bool var, std::string path_access, int status_code, std::map<unsigned int, std::string> map_Codestatus,Location *Locations,  Request     *request, std::string header);
        std::string	get_time(void);
        std::string	get_content_type(const std::string &path, const bool &check);
        std::string	getdayofweek(const int day);
        std::string	getmonth(const int month);
};


#endif