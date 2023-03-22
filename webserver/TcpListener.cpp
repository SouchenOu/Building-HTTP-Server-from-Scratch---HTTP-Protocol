/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpListener.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:38 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:39 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "TcpListener.hpp"
#include "iostream"


// constructer

// TcpListener::TcpListener(int ip_address, int port)
// {

// }

int TcpListener::init()
{
    // create a socket
    fd_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_socket == 0)
    {
        perror("Problem creating a Socket.....");
        exit(0);
    }
    // bind the ip address and port to that socket (giving the ip port and ip address for that socket )

    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_port = htons(port);
    add.sin_addr.s_addr = INADDR_ANY; // could also use inet_pton
    //inet_pton(AF_INET, ip_address, &add.sin_addr);

    if(bind(fd_socket, (sockaddr*)&add,sizeof(add)) == 0)
    {
        perror("Problem binding a Socket.....");
        exit(0);

    }

    if(listen(fd_socket, SOMAXCONN) == 0)
    {
        perror("Problem binding a Socket.....");
        exit(0);
    }

    /* Initializes the file descriptor set fdset to have zero bits for all file descriptors.
    // FD_ZERO(&fdset)  */
    FD_ZERO(&set_file_des);

    // add our first socket we are interested in interacting with
    //it is important that this socket is added for our server or else we wont hear incoming connection


    /* FD_SET(fd, &fdset)  
    // Sets the bit for the file descriptor fd in the file descriptor set fdset.*/
    FD_SET(fd_socket, &set_file_des);

    return 1;


}

int  TcpListener::run()

{
    // this will be changed by \quit command

    bool running = true;
}