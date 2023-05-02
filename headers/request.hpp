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
        // int file_file_descriptor;
        
   
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

        // setters
        void set_Path(std::string path);
        void set_path_of_file_dm(std::string path_of_file);

        int check_request_with_config_file(const std::set<server*> &servers);
        void Path_of_FileAccess();
        std::string path_of_file();
        //std::string response_header(int fileSize, bool test);
        int get_indice();
        void Parcing_request(std::string buffer);
        std::string get_request_header(std::string name);
        bool check_client_max_body_size(unsigned int size);
        std::string check_error_page(int Status_code);
        int check_which_location_compatible();
       map<unsigned int, string> Status_codes_means(void);
        





};





#endif
