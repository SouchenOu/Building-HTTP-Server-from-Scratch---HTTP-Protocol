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

class response
{
  
    public:

        //constructers
        response();
        //~destructer
        ~response();

        //used function

        std::string response_header(int size_of_file, bool var, std::string path_access);
};


#endif