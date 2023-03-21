/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:10:17 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 18:10:19 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.hpp"
#include "unistd.h"



// constructer

ft::test::test() : Server(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
    launch();
}


void ft::test::accepter()
{
    /*accepter we are going to skip the part where actually tests to make sure everything is working and we are just going to assume that 
    // it works.*/
    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    new_socket = accept(get_socket()->get_ident_socket(), (struct sockaddr *)&address, (socklen_t*)&addrlen);
    // we finally have connected sockets between a client and server(When you visit Ip address of your server from a web browser)
    // then read from the connection 
    read(new_socket, buffer, 30000);
}

void ft::test::handler()
{
    std::cout << buffer << std::endl;

}

void ft::test::responder()
{
    char hello[100] = "Hello from server";

    write(new_socket, hello, strlen(hello));
    close(new_socket);
}

//then we goinf to need our actual launch function that is the infinite loop that will be doing these things succession and one thing i want to point out about the infinite loop, is that when it gets to the acceptor
//it seems what it is doing is once it gets to this line, where it is waiting to accept, if there is nothing trying to be accepted then it is just going to wait.


void ft::test::launch()
{
    while(true)
    {
        std::cout << "Waiting......\n";
        accepter();
        handler();
        responder();
        std::cout << "Everthing is done.....\n";
    }
}