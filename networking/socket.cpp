/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:02 by souchen           #+#    #+#             */
/*   Updated: 2023/03/17 09:50:03 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "socket.hpp"

/*working on the simplest component of a web server or the most basic component of programming in networks that is a sockets
// and a socket is just a thing that allows your operating system to connect to a network in  a particular way, and 
you would use this whether you are building a server a client or a peer-to-peer network


*/

/* create a very general object or class that is going to represent a socket make it very easy to construct one also be easily impostable
 into other functionalities so whether i want to build a client , a web server or a peer to peer network whatever i want to build 
 it is going to need a socket and so i'm going to build an object for a socket to make them really easy to implement 
 
 */

ft::Socket::Socket(int domain, int service, int protocol, int port, u_long ip_address)
{
    // *****************establish a connection
    if(connection = socket(domain,service, protocol) == 0)
    {
        perror("In socket");
        exit(0);
    }
    //******************define address structure
    address.sin_family = domain;
    address.sin_port = htons(port);
    // and finaly we need to set the interface on which this socket is running that is your ip address(your machine is IP address)

    //it is ip_address but we need to convert it, so it is the unsigned long that we are giving it, is in bytes order for
    //the host system, and we want it to be int the bytes order of the network so we will use a similar function htonl
    address.sin_addr.s_addr = htonl(ip_address);



     
    //now we have made the connection and we need to bind that to the network, that is to name the socket.
    // so we will use bind() function 

}


