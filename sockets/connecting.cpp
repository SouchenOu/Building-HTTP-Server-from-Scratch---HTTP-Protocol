/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connecting.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:16:36 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 11:16:37 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connecting.hpp"

//constructer

ft::connecting::connecting(int domain, int type,int protocol, int port, u_long address) : SocketSimple(domain, type, protocol, port, address)
{
    set_connection(connect_to_network(get_ident_socket(), get_address()));
    test_connection(get_connection());
}

int ft::connecting::connect_to_network(int identify_sock, struct sockaddr_in address)
{
    return connect(identify_sock, (struct sockaddr *)&address, sizeof(address));
}
