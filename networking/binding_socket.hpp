/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding_socket.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:44:39 by souchen           #+#    #+#             */
/*   Updated: 2023/03/17 15:44:40 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDING_SOCKET_HPP
#define BINDING_SOCKET_HPP

#include "iostream"
#include "socket.hpp"




// we want to access to all the function of class Socket, the binding_socket class will inherate class Socket
namespace ft
{
    class BindingSocket : public Socket
    {
        public:
            BindingSocket(int domain, int service, int protocol, int port, u_long ip_address):Socket(domain,service,protocol,port, ip_address);
            int connect_to_network(int identify_sock, struct sockaddr_in address);
    };
};


#endif

