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

#include "cstring"
#include "string"
#include "iostream"
using namespace std;

class Location
{
    private:
        string root;
        string try_files;
        string  return_line;
        string  alias;
    public:
    // constructer
        Location();
    //destructer
        ~Location();

    // setters

    void set_root(string root);
    void set_try_files(string try_files);
    void set_return_line(string return_line);
    void set_alias(string alias);

    // getters

    string get_root();
    string get_try_files();
    string get_return_line();
    string get_alias();


};