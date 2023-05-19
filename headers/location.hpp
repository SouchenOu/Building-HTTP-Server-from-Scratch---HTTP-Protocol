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

#include "tools.hpp"

class Location
{
    private:
        std::string root;
        std::string try_files;
        std::string  return_line;
        std::string  alias;
        int http_redirection;
        std::string  autoindex;
        int upload_enable;
        std::string index;
        std::string path;
        std::vector<std::string> http_allow_method;
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
    void set_autoindex(std::string autoindex);
    void set_upload_enable(int upload_enable);
    void set_index(std::string index);
    void set_path(std::string Path);

    // getters

    std::string get_root();
    std::string get_try_files();
    std::string get_alias();
    int  get_http_redirection();
    std::string get_return_line();
    std::string get_autoindex();
    int get_upload_enable();
    std::string get_index();
    std::string get_path();
    std::vector<std::string>	get_http_allow_method(void);
    void push_allow_HTTP_methods(std::string method_allow);


    // function push_in_location


};

#endif