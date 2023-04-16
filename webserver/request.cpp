/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:36:06 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:36:08 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/headers.hpp"
# define white_espace "; \t"




// constructers


Request::Request()
{
    std::cout << "Send a request\n";
}

Request::Request(const std::string buffer)
{
    string content_type;
  
	vector<string> request_Headers = ft_divise(buffer, "\r\n");
    

    vector<string>::iterator iter = request_Headers.begin();
    // std::cout << "First-->" << *iter << endl;
    //vector<string> First_line = ft_divise(*iter, white_espace);
    //path = *iter + 1;

    while(iter != request_Headers.end())
    {
        vector<string> First_line = ft_divise(*iter, ": ");
        // std::cout << "First_line[0]-->" << First_line[0] << endl;
        // std::cout << "First_line[1]-->" << First_line[1] << endl;
        // std::cout << "First_line[2]-->" << First_line[2] << endl;
        vector<string>::iterator i = First_line.begin();

        if(First_line.size() < 2)
        {
            std::cout << "empty line\n";
            break ;
        }
        if(*i == "Host")
        {
            vector<string> split_Host = ft_divise(First_line[1], ":");
         
            if((First_line.size() != 3  && !(First_line.size() == 2 && First_line[1] == "localhost")) || First_line[1].size() == 0)
            {
                break ;
            }else{
                // server and browser exchange meta information about the document via the HTTP header.
                headers.insert(pair<string,string>("Host", First_line[1]));
                headers.insert(pair<string,string>("Port",First_line[2]));
            }
        }else
            headers.insert(pair<string, string>(First_line[0], First_line[1]));


            // std::map<string, string>::iterator it;
            // std::cout << "Headers******\n";
            // for(it = headers.begin(); it != headers.end(); it++)
            // {
            //     std::cout <<"*************\n";
            //     std::cout << "First->" <<it->first << endl;
            //     std::cout << "Second->"<<it->second  << endl;
            //     std::cout <<"*************\n";

            // }

        iter++;

    }
     // In POST request we find content-length ,content-type, origin and referer
    size_t found;
    found = buffer.find("content-type");
    // npos means end of buffer
    if(found != string::npos)
    {
        content_type = buffer.substr(found, buffer.find('\n', found));
    }



	
}

// // destructer
Request::~Request()
{

}

//getters

std::map<string, string> Request::get_headers()
{
    return headers;
}

std::string Request::get_Path()
{
    return Path;
}

std::string Request::get_type_request()
{
    return type_request;
}

void Request::set_Path(std::string path)
{
    this->Path = path;
}

