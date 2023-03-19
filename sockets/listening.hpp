/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:31:15 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 13:31:17 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LISTENING_HPP
#define LISTENING_HPP



#include "binding_socket.hpp"
namespace ft
{
    class listening : public BindingSocket
    {
        private:
            int backlog;
            int listennn;
        //constructers
        public:
            listening(int domain, int type, int protocol, int port, u_long address, int bck);
            void listen_funct();

    };
};



//backlog : you can think of -->as a line, so if you imagine that iam a server and i can only serve one person at a 
//time ,in the future we can actually set it so that it serves multiple people at once through threading.
// so the backlog is the maximum length of our line, so lets say i can serve 10 people in the line.
//when the 10 person gets in the line, we are just going to kick them out  

#endif