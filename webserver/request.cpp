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


#include "../headers/tools.hpp"
# define white_espace "; \t"
#include <fcntl.h>
// #include <filesystem>
// #include "iostream"
// #include <iostream>
// #include <fstream>
// #include <cstdio>
// #include <cstring>
// #include <filesystem>
// #include <unistd.h>
// #include <sys/socket.h>
// #include <sys/un.h>
// # include <sys/stat.h>
// # include <dirent.h>



// constructers


Request::Request()
{
    std::cout << "Send a request\n";
}

Request::Request(std::string buffer):Status_Code(0)
{
  
	Parcing_request(buffer);

}

// // destructer
Request::~Request()
{
	std::cout << "request destructer\n";
}
void Request::Parcing_request(std::string buffer)
{
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
         
            if(First_line.size() != 3)
            {
                break ;
            }else{
                // server and browser exchange meta information about the document via the HTTP header.
                request_headers.insert(pair<string,string>("Host", First_line[1]));
                request_headers.insert(pair<string,string>("Port",First_line[2]));
            }
        }else
            request_headers.insert(pair<string, string>(First_line[0], First_line[1]));


            // std::map<string, string>::iterator it;
            // std::cout << "request_headers******\n";
            // for(it = request_headers.begin(); it != request_headers.end(); it++)
            // {
            //     std::cout <<"*************\n";
            //     std::cout << "First->" <<it->first << endl;
            //     std::cout << "Second->"<<it->second  << endl;
            //     std::cout <<"*************\n";

            // }

        iter++;

    }
}
//getters



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
	// (void) request_headers;
	string Host;
	unsigned int port;
	string path_navigate;
	path_navigate = Path;
	std::set<server*>::iterator iter1;
	std::set<string>::iterator iter2;
	std::set<server*>::iterator iter3;
	this->Servers =  NULL;
	if(request_headers.find("Host") != request_headers.end())
	{
		Host = request_headers.find("Host")->second;
	}
	else 
	{
		Host = "";
		Status_Code = 400;
		std::cout << "Bad request\n";
		return 0;
	}
	//std::cout << "Host-->" << Host << endl;

	if(request_headers.find("Port") != request_headers.end())
	{
		port = atoi(request_headers.find("Port")->second.c_str());
	}else
	{
		port = 0;
		Status_Code = 400;
		return 0;
	}
	
	for(iter3 = servers.begin(); iter3 != servers.end(); iter3++)
	{
		if((*iter3)->get_port_listen() == port )
		{
			this->Servers = (*iter3);
			break ;
		}
	}

	for(iter1 = servers.begin(); iter1 != servers.end(); iter1++)
	{
		set<string> server_names = (*iter1)->get_server_name();
		for(iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
		{
			if((*iter2) == Host  && (*iter1)->get_port_listen() == port)
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

	this->Locations = NULL;
	return 1;

}

void Request::path_of_file()
{
	string Path_in_request;
	string tmp_file;
	int file_des;
    if(Locations == NULL || Servers == NULL)
    {
		std::cout << "failed\n";
        path_of_file_dm = "";
		return ;
    }

	
	Path_in_request = Path; // in my case i have / 
	path_of_file_dm = Servers->get_root();

	//if(strcmp(Path_in_request, "/") == 0)
	if (Path_in_request.compare("/") == 0)
	{
		
		if (Locations && Locations->get_index().length())
			Path_in_request += '/' + Locations->get_index();
		else
			Path_in_request += '/' + Servers->get_index();
	}
	//return Path_in_request;
	if (Path_in_request.find(Locations->get_path()) == 0)
	{
		Path_in_request = Path_in_request.substr(Locations->get_path().length());
		// std::cout << "our path->" << Path_in_request << endl;
		path_of_file_dm += Locations->get_root();
		// std::cout << "path->" << path_of_file_dm << endl;
	}
	//std::cout << "after\n";
	if(is_directory(path_of_file_dm + Path_in_request))
	{
		std::cout << "nop\n";
		tmp_file = path_of_file_dm + Path_in_request;
	}
	else
	{
		tmp_file = path_of_file_dm + '/' + Path_in_request;
	}
	if(tmp_file[tmp_file.length() - 1] == '/')
	{
		if(Locations->get_index().length())
		{
			tmp_file = tmp_file + Locations->get_index();
		}
	}
	file_des = open(tmp_file.c_str(),O_RDONLY);
	if(Path[Path.size() - 1] == '/' && file_des <= 0)
	{
		std::cout << "failed or what\n";
		path_of_file_dm = Servers->get_root() + '/';
	}
	else
		path_of_file_dm = tmp_file;

	close(file_des);
	std::size_t found = path_of_file_dm.find("//");
	if(found != std::string::npos)
	{
		path_of_file_dm.replace(found, 2 ,"/");
	}


}

std::string Request::give_the_header(int fileSize, bool var)
{
	string str;
	// ifstream our_file(path_of_file_dm.c_str());

	// while(getline(our_file, str))
	// {
	// 	std::cout << "txt->" << str << endl;
	// }
	
	if(var == 0)
	{
		ifstream our_file(path_of_file_dm.c_str(),std::ios::in);
		// while(getline(our_file, str))
		// {
		// 		std::cout<< "str-->\n";

		// 		std::cout << str << endl;
		// }
		// position at end of fileObject
		our_file.seekg(0, ios::end);
		//Say we have entered 20 characters in a text file, and you want to read it.
//		But along with reading you also want to know the position of the last position in the text file.
		fileSize = our_file.tellg();
	}
	//  std::cout << "file_size == " << fileSize << endl;

	stringstream response_header;
	response_header << "Content-Length: " << fileSize << endl;
	response_header << "Connection: Closed" << endl;

	return response_header.str();
	
}


int Request::get_indice(int &file_des)
{
	// std::cout << "path-->" << path_of_file_dm << endl;
	if(Status_Code == 0)
	{
		Status_Code = 200; //OK
	}
	else if(Status_Code == 400) // BAD_REQUEST
	{
		// should have error_page
		std::cout << "error_page\n";
		return 0;
	}
	
	file_des = open(static_cast<const char *>(path_of_file_dm.c_str()), O_RDONLY);
	//std::cout << "file-->" << file_des << endl;
	return 0; 
}


