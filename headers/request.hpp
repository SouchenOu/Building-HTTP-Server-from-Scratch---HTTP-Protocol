/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:40:54 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:35:53 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "headers.hpp"


class Request
{

    private:

        std::map<std::string, std::string> headers;
        std::string Path;
        std::string type_request;
        
   
    public:

        // constructers

        Request();
        Request(const std::string buffer);
        // destructer
        ~Request();


        //some used functions
        std::map<std::string, std::string> get_headers();


        // getters

        std::string get_Path();
        std::string get_type_request();

        // setters
        void set_Path(std::string path);
       

       
        





};





#endif
