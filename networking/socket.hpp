/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:41 by souchen           #+#    #+#             */
/*   Updated: 2023/03/17 09:50:43 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SOCKET_HPP
#define SOCKET_HPP
//socket library
#include "sys/socket.h"
#include "netinet/in.h"

namespace ft
{

    // struct sockaddr_in
    // {
    //     __uint8_t   sin_len;
    //     sa_family_t sin_family;
    //     in_port_t   sin_port;
    //     char        sin_zero[8];
    // };
    class  Socket
    {
        private:
            int ident_socket;
            struct sockaddr_in address;
            int connection;
            //constructer
        public:
            Socket(int domain, int type, int protocole, int port, u_long ip_address);
            // in order to force the user to do one of (connect() or bind()) we use this virtual function,
            // so now we have to create a class that inherits from socket and will implement this virtual function
            //(In new file binding_socket) 
            virtual int connect_to_network(int identify_sock, struct sockaddr_in address) = 0;
            //getters

            int get_ident_socket();
            int get_connection();
            struct sockaddr_in get_address();

            // function to test if the connection is established or not
            void test_connection(int);

    };
    // we will use a class interface and specify a virtual function and this is going to make anyone  inheriting 
    //this class template, they are going to be forced to imlement this connection function in some way 
    // and they can specify whether it is bind or connect 
};


#endif