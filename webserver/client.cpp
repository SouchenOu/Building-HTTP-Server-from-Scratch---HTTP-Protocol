/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:23:29 by souchen           #+#    #+#             */
/*   Updated: 2023/04/06 14:23:30 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.hpp"

Client::Client(int new_listen_fd, set<server*>& servers) : fd_descripter(0)
{
	//client_len = sizeof(client_addr);
	fd_descripter = accept(new_listen_fd, get_sockaddr(), get_addr_len());
	inet_ntop(AF_INET, &(client_addr.sin_addr), client_ipv4_str, INET_ADDRSTRLEN);
}


