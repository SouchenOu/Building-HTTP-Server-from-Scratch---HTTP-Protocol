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

#include "../headers/headers.hpp"

class server;

class response
{




    public:

        //constructers
        response();
        //~destructer
        ~response();

        //used function

        void server_s();
        void response_preparation(const std::set<server*> &servers, std::map<string, string> headers);
};


#endif