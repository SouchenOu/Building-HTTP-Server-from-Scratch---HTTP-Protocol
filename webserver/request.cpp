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

Request::Request(const std::string buffer):Status_Code(0)
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
    // size_t found;
    // found = buffer.find("content-type");
    // // npos means end of buffer
    // if(found != string::npos)
    // {
    //     content_type = buffer.substr(found, buffer.find('\n', found));
    // }



	
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
		Status_Code = 400;
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

	
	return 1;

}

void Request::path_of_file()
{
	string Path_in_request;
	string tmp_file;
	int file_des;
    if(Locations == NULL || Servers == NULL)
    {
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
		path_of_file_dm += Locations->get_root();
	}

	if(is_directory(path_of_file_dm + Path_in_request))
	{
		std::cout << "yes\n";
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
	if(file_des <= 0)
	{
		path_of_file_dm = Servers->get_root();
	}
	else
		path_of_file_dm = tmp_file;

	// close(file_des);
	std::size_t found = path_of_file_dm.find("//");
	if(found != std::string::npos)
	{
		path_of_file_dm.replace(found, 2 ,"/");
	}
	//std::cout << "our file is" << path_of_file_dm << endl;


}

std::string Request::give_the_header(int fileSize, bool test)
{
	if(test == 0)
	{
		ifstream our_file(path_of_file_dm.c_str());
		// position at end of fileObject
		our_file.seekg(0, ios::end);
		fileSize = our_file.tellg();
	}
	

	stringstream header;
	header << "Content-Length: " << fileSize << endl;
	header << "Connection: Closed" << endl;

	return header.str();
	
}


int Request::get_indice()
{
	std::cout << "path-->" << path_of_file_dm << endl;
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
	if(is_directory(path_of_file_dm))
	{
		std::cout << "nop\n";
		if(path_of_file_dm[path_of_file_dm.size() - 1] == '/' && Locations->get_autoindex() == 1)
		{
			Status_Code = 200;
			return 1;
		}else
		{
			Status_Code = 403;
		}

	}
	return 1;
}


void Request::index_auto(std::string &test)
{
	stringstream auto_index;
	auto_index << "	<html lang=\"en\">\n\
					<body style=\"background-color: grey; color: lightgrey;\">\n\
					<div style=\"display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;\">\n\
						<h1>Auto Index</h1>\n";
	auto_index << path_of_file_dm.substr(Servers->get_root().length() + 1);
	//std::cout << "here-->" << path_of_file_dm.substr(Servers->get_root().length() + 1) << endl;
	//std::cout << "contenue->" << auto_index.str() << endl; 
	// DIR *dir;
	// struct dirent *ent;
	// if ((dir = opendir(path_of_file_dm.c_str())) != NULL)
	// {
	// 	while ((ent = readdir(dir)) != NULL)
	// 	{
	// 		string link = ent->d_name;
			
	// 		if (is_directory(path_of_file_dm + '/' + link))
	// 		{

	// 			link += '/';
	// 		}
	// 		if (is_directory(Path) && Path[Path.size() - 1] != '/')
	// 			Path += '/';
	// 		auto_index << "<p><a href=\"" << link << "\" class=\"active\">" << link << "</a></p>\n";
	// 	}
	// 	closedir (dir);
	// }
	// else
	// {
		
	// 	exit(EXIT_FAILURE);
	// }
	// auto_index << "	</div>\n\
	// 				</body>\n\
	// 				</html>";
	Status_Code = 200;
	test = auto_index.str();
	//std::cout << "test = " << test << endl;
}