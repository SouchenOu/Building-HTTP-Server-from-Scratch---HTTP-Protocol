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

    public:
        // constructer
        WebBrowsers();
        WebBrowsers(int new_listen_fd, set<server*>& servers);
        //destructer
        ~WebBrowsers();



        //getters
        int get_file_descriptor()
        {
            return file_descriptor;
        }
       
        void set_file_descriptor(int fd)
        {
            this->file_descriptor = fd;
        }

        struct sockaddr* get_address_client(void);
        
};



#endif