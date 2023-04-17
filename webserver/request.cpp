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
    // path = *iter + 1;

	vector<string> line = ft_divise(*iter , white_espace);

	Path = line[1];
	version_http = line[2];

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


int Request::check_request_with_config_file(const std::set<server*> &servers)
{
	// (void) servers;
	// (void) path;
	// (void) headers;
	string Host;
	unsigned int port;
	string path_navigate;
	path_navigate = Path;
	std::set<server*>::iterator iter1;
	std::set<string>::iterator iter2;
	std::set<server*>::iterator iter3;
	this->Servers =  NULL;
	if(headers.find("Host") != headers.end())
	{
		Host = headers.find("Host")->second;
	}
	else 
	{
		Host = "";
		code = 400;
		std::cout << "Bad request\n";
		return 0;
	}
	//std::cout << "Host-->" << Host << endl;

	if(headers.find("Port") != headers.end())
	{
		port = atoi(headers.find("Port")->second.c_str());
	}else
	{
		port = 0;
		code = 400;
		return 0;
	}
	// std::cout << "Port-->" << port << endl;
	for(iter3 = servers.begin(); iter3 != servers.end(); iter3++)
	{
		if((*iter3)->get_port_listen() == port )
		{
			this->Servers = (*iter3);
		}
	}

	for(iter1 = servers.begin(); iter1 != servers.end(); iter1++)
	{
		set<string> server_names = (*iter1)->get_server_name();
		for(iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
		{
			if((*iter2) == Host && (*iter1)->get_port_listen() == port)
			{
				this->Servers = (*iter1);
			}
		}

	}

	if(this->Servers == NULL)
	{
		std::cout << "No Server is compatible\n";
		return 0;
	}

	//For location
	std::list<Location> locations = Servers->get_locations();
	if(locations.size() == 0)
	{
		Locations = NULL;
		return 0;
	}
	//std::set<Location>::iterator i1;

	for(std::list<Location>::iterator i1 = locations.begin(); i1 != locations.end() ; i1++)
	{
		if((i1)->get_path() == path_navigate)
		{
			this->Locations = new Location(*i1);
			return 1;
		}
	}

	
	return 1;

}

void Request::path_of_file()
{
	// string target_tmp;
    // if(Locations == NULL || Servers == NULL)
    // {
    //     path_of_file_dm = "";
	// 	return ;
    // }

	// path_of_file_dm =  Servers->get_root();
	// target_tmp = Path;
	// //if(strcmp(target_tmp, "/") == 0)
	// if (target_tmp.compare("/") == 0)
	// {
	// 	if (Locations->get_index().length() != NULL)
	// 		target_tmp += '/' + Locations->get_index();
	// 	else
	// 		target_tmp += '/' + Servers->get_index();
	// }

	// if (target_tmp.find(Locations->get_path()) == 0)
	// {
	// 	target_tmp = target_tmp.substr(Locations->get_path().length());
	// 	path_of_file_dm += Locations->get_root();
	// }




}
