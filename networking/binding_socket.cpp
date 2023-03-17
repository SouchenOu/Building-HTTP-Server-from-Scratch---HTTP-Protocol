/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding_socket.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:43:26 by souchen           #+#    #+#             */
/*   Updated: 2023/03/17 15:43:28 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binding_socket.hpp"
#include "socket.cpp"




ft::BindingSocket::BindingSocket(int domain, int type, int protocol, int port, u_long ip_address) : Socket(domain, type, port, ip_address)
{

        int connection = connect_to_network(get_ident_socket(), get_address());
        test_connection(connection);

}



int ft::BindingSocket::connect_to_network(int identify_sock, struct sockaddr_in address)
{
    return bind(identify_sock, (struct sockaddr *)&address, sizeof(address));
}
