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

#include "tools.hpp"
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
            Location                    *Locations;
            Request     		*request;
            std::string path_access;
            std::string response_buffer;
            unsigned int send_byte;
            int indice;
            int file_file_descriptor;
            int autoindex;
            int cmp;
            bool check_error ;


    public:
        // constructer
        WebBrowsers();
        WebBrowsers(std::set<server*>& servers);
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
        void ThePath_of_acces_file();
        void prepareResponse();
        // int check_request_with_config_file(const std::set<server*> &servers, std::map<std::string, std::string> headers, std::string path);
        void Connection(int new_listen_fd);
        int Read_request();
        int send_response();
        int send1();
        int send2();
        void check_error_page();
        int	EndChunked(std::string& buffer,const std::string& end_chunk);

        
};



#endif