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
#include "request.hpp"

class server;
class response;
class   WebBrowsers
{
    private:
            int file_descriptor;
            struct sockaddr_in	address_client;
            int     recvStatus;
            std::string read_buffer;
            int value;
            int check_fd;
            response			*Response;
            std::set<server*>&		servers;
            Request     		*request_Headers;
            std::string send_buffer;
            unsigned int send_byte;
            int indice;
            int file_file_descriptor;
            char				client_ipv4_str[INET_ADDRSTRLEN];


    public:
        // constructer
        WebBrowsers();
        WebBrowsers(int new_listen_fd, std::set<server*>& servers);
        //destructer
        ~WebBrowsers();



        //getters
        int get_file_descriptor();
        int get_recvStatus();
        int get_value();
        int get_check_fd();
        int get_indice();
       
       //setters
        void set_file_descriptor(int fd);
        void set_recvStatus(int recvStatus);
        struct sockaddr* get_address_client(void);
   


        // some used functions
        void check_request();
        // int check_request_with_config_file(const std::set<server*> &servers, std::map<std::string, std::string> headers, std::string path);
        void Connection(int new_listen_fd);
        int Read_request();
        void send_response();
        void send1();
        void send2();
        
};



#endif