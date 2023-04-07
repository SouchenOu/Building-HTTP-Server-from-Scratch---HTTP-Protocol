/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:12:34 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 17:12:36 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "iostream"
#include "../sockets/listening.hpp"
//include our sockets object
// include "../sockets/"

namespace ft
{
    class Server
    {
        private:
        // i want our socket to be a private member variable
            //defines a space in memory to hold a socket without actually instantiating it 
            listening *socket;
            virtual void accepter() = 0;
            virtual void handler() = 0;
            virtual void responder() = 0;
        public:
            Server(int domain, int type, int protocol, int port, u_long address, int bklg);
            virtual void launch() = 0;
            listening *get_socket();


    };
}


// first with accept() we test that connection to make sure it worked and  the client make a requiste to the server then reading what that requeste is then writing a response 

#endif
