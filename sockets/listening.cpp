/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:31:08 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 13:31:10 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listening.hpp"



//before a client can connect to a server, the server should have a socket that is prepared to accept  the connections. 
//so we create a socket by using function socket() and we identifier this socket by using function bind()
// then the listen() system call tells a socket that it should be capable of accepting incoming connections.


ft::listening::listening(int domain, int type, int protocol, int port, u_long address, int bck): BindingSocket(domain, type, protocol,port,address)
{
    backlog = bck;
    listen_funct();
    test_connection(listennn);
}

void ft::listening::listen_funct()
{
    listennn =  listen(get_ident_socket(), backlog);
}

// The original socket that was set up for listening is used onley for accepting connections, not for exchanging data