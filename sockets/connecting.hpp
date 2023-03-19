/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connecting.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:16:42 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 11:16:43 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONNECTING_HPP
#define CONNECTING_HPP

#include "iostream"
#include "SocketSimple.hpp"
namespace ft
{
    class connecting : public SocketSimple
    {
        //constructer
        connecting(int domain, int type, int protocol,int port, u_long address);
        // Our virtual function

        int connect_to_network(int identify_sock, struct sockaddr_in address);



    };
}


#endif