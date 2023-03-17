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
#include "stdio.h"
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
            int connection;
            struct sockaddr_in address;
            //constructer
        public:
            Socket(int domain, int service, int protocole, int port, u_long ip_address);

    };
};


#endif