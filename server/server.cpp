/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:40:23 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 09:40:25 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"

ft::Server::Server(int domain, int type, int protocol, int port, u_long address, int bklg)
{
 // so what iam doing here is i have this null pointer (socket) and iam instantiating a new 
 //listening socket object, and iam putting that listening socket object into this memory location, or iam pointing the memory location to that 
 //new object 
    socket = new listening(domain, type, protocol, port, address, bklg);  
}

ft::listening *ft::Server::get_socket()
{
    return socket;
}