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

ft::listening::listening(int domain, int type, int protocol, int port, u_long address, int backlong): BindingSocket(domain, type, protocol,port,address)
{
    backlog = backlog;
    listen_funct();
    test_connection(listennn);
}

void ft::listening::listen_funct()
{
    listennn =  listen(get_connection(), backlog);
}