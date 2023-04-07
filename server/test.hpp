/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:10:22 by souchen           #+#    #+#             */
/*   Updated: 2023/03/19 18:10:24 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEST_HPP
#define TEST_HPP


#include "server.hpp"

namespace ft
{
    class test : public Server
    {
        private:
            char buffer[30000];
            int new_socket;
            void accepter();
            void handler();
            void responder();
        public:
            test();
            void launch();
    };

}






#endif