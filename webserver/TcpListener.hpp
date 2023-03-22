/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpListener.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// This is gonna be a header file for the class (The interface that people use to access our class)

#pragma once
#include <iostream>
#include "netinet/in.h"
#include "sys/select.h"

#include <string>
#include <sstream>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>




class TcpListener
{

    private:
        const char* ip_address;  // Ip address server will run on
        int port; // Port for the web server
        int fd_socket; //internal file_discriptor socket for the listening socket
        fd_set   set_file_des; // fule discriptor set we need it to testing a given socket for reability using the readfds parameter of the select function
        
    public:
    // constructer

    TcpListener(const char* ip_address, int port)
    {
        ip_address = ip_address;
        port = port;
    }
    // initialize the listenner
    int init();
    // Run the listenner
    int run();



};


