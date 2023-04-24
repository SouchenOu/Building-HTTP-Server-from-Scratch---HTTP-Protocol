/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding_socket.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:36:06 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:36:08 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/binding_socket.hpp"

#include "netinet/in.h"

int binding_socket(int identify_sock, struct sockaddr_in address)
{
    return bind(identify_sock, (struct sockaddr *)&address, sizeof(address));
}