/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:40:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/28 19:30:36 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cstring"
// #include "string"
// #include "iostream"

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "headers.hpp"
// using namespace std;

class Location
{
    private:
        std::string root;
        std::string try_files;
        std::string  return_line;
        std::string  alias;
        int http_redirection;
        int  autoindex;
        std::string index;
        std::string path;
        std::vector<std::string> http_method;
    public:
    // constructer
        Location();
    //destructer
        ~Location();

    // setters

    void set_root(std::string root);
    void set_try_files(std::string try_files);
    void set_return_line(std::string return_line);
    void set_alias(std::string alias);
    void set_http_redirection(int http_redirection);
    void set_autoindex(int autoindex);
    void set_index(std::string index);
    void set_path(std::string Path);

    // getters

    std::string get_root();
    std::string get_try_files();
    std::string get_return_line();
    std::string get_alias();
    int  get_http_redirection();
    int get_autoindex();
    std::string get_index();
    std::string get_path();
    void allow_HTTP_methods(std::string method_allow);


    // function push_in_location


};

#endif