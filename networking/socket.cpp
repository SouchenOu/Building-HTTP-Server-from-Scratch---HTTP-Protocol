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
#include "iostream"

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
    // *****************Create a socket(Establish a socket)
    if(ident_socket = socket(domain,service, protocol) == 0)
    {
        perror("Problem creating a Socket.....");
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


    /* I think that binding was something we were going to do on every socket, but when i search i'm noticing that the bind function is 
    only called on the server side, but on the client side code, bind operation replaced with this connect function, and we can see 
     that connect() function has the same parameter */
     /* so instead of just binding it by default we need to be  able to specify whether we bind or connect so it could force the user to specify
     //whether they want to bind or connect in the constructor with a boolen (and you set it to true for bind and you set it to false for connect )
     // but the better is use this as a class interface and specify a virtual function and this is can make anyone inheriting 
     //this class template , they are going to forced to implement this connection function in some way and they can specify whether
     //it is bind or connect  */


     // so the connection will be made  using this connect to network function which is either going to call (bind or connect)
 
        // establish the connection 
        connection = connect_to_network(ident_socket, address);
        test_connection(connection);
}

// Test connection virtual function
void ft::Socket::test_connection(int to_test)
{
    if(to_test < 0)
    {
        perror("Faied to connect..");
        exit(0);
    }
}



// getters

struct sockaddr_in ft::Socket::get_address()
{
    return address;
}

int ft::Socket::get_connection()
{
    return connection;
}
int ft::Socket::get_ident_socket()
{
    return ident_socket;
}


