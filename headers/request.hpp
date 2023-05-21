/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:40:54 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:35:53 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "tools.hpp"

class server;
class Location;
class Request
{

    private:

        std::map<std::string, std::string> request_headers;
        std::string Path;
        std::string type_request;
        server  *Servers;
        Location    *Locations;

        //HTTP response status codes indicate whether a specific HTTP request has been successfully completed.
        int Status_Code;
        std::string path_of_file_dm;
        std::string version_http;
        size_t count_pos;
        int indice_body;
        std::string content_type;
        std::string transfer_encoding;
        int content_length_exist;
        std::string cookie;
        
   
    public:

        // constructers

        Request();
        Request(std::string buffer);
        // destructer
        ~Request();


        //some used functions
        std::map<std::string, std::string> get_headers();


        // getters

        std::string get_Path();
        std::string get_type_request();
        std::string get_path_of_file_dm();
        int get_Status_code();
        int get_indice_body();
        std::string get_content_type();
        int get_content_length_exist();

        // setters
        void set_Path(std::string path);
        void set_path_of_file_dm(std::string path_of_file);
        void set_Status_code(int code);
        void set_indice_body(int indice);
        int check_request_with_config_file(const std::set<server*> &servers);
        void Path_of_FileAccess();
        std::string path_of_file();
        //std::string response_header(int fileSize, bool test);
        int check_auto_index(std::string path_access);
        void Parcing_request(std::string buffer);
        bool check_client_max_body_size(unsigned int size);
        std::string error_pages(int Status_code);
        int check_which_location_compatible();
       std::map<unsigned int, std::string> Status_codes_means(void);
       int check_cgi();
       std::string cgi_start(std::string &body);
       char ** get_the_path(std::string extention_name);
       char * ft_strdup(std::string path);
       std::string &get_request_header(std::string element);
       void ADD_body(std::string buffer);
       void auto_index(std::string &str, std::string path_access);
       Location *get_location();
       void delete_request(std::string &path);
       std::string get_transfer_encoding();
    
        





};





#endif
