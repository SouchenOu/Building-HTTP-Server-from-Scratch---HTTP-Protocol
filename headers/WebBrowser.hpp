/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebBrowser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:23:20 by souchen           #+#    #+#             */
/*   Updated: 2023/04/06 14:23:22 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WEBBROWSER_HPP
#define WEBBROWSER_HPP

#include "headers.hpp"

class   WebBrowsers
{
    private:
            int file_descriptor;
            struct sockaddr_in	address_client;
            int     recvStatus;

    public:
        // constructer
        WebBrowsers();
        WebBrowsers(int new_listen_fd);
        //destructer
        ~WebBrowsers();



        //getters
        int get_file_descriptor();
        int get_recvStatus();
       
       //setters
        void set_file_descriptor(int fd);
        void set_recvStatus(int recvStatus);
        struct sockaddr* get_address_client(void);
        
};



#endif