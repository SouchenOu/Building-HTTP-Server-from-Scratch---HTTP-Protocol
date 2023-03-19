/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:36:29 by souchen           #+#    #+#             */
/*   Updated: 2023/03/16 16:51:13 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"
#include "listening.hpp"
using namespace std;
// #include "SocketSimple.hpp"
//steps:
/******1: Implementing TCP
 * to implement tcp we have to learn TCP socket programming
 * There are a few steps involved in using sockets:
 * 1: create socket
 * 2:identify the socket
 * 3: on the server, wait for an incoming connection
 * 4: Send and receive messages
 * 5:Close the socket
 * */


int main()
{
    std::cout << "Start.......\n";
    // std::cout << "CREATE A SOCKET" << std::endl;
    //ft::SocketSimple sock = ft::SocketSimple(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
    std::cout << "Binding a socket....\n";

    ft::BindingSocket bind_socket = ft::BindingSocket(AF_INET, SOCK_STREAM, 0,80, INADDR_ANY);

    ft::listening listen = ft::listening(AF_INET, SOCK_STREAM,0 , 80, INADDR_ANY, 10);
  
    std::cout << "connect with Successs!!\n";


}

