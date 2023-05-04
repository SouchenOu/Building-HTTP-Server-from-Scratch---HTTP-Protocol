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


// constructers


Request::Request()
{
    std::cout << "Send a request\n";
}

Request::Request(std::string buffer):Locations(0),Status_Code(0)
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
	vector<string> request_divise = ft_divise(buffer, "\r\n");
    

    vector<string>::iterator iter = request_divise.begin();
    // std::cout << "First-->" << *iter << endl;
    //vector<string> First_line = ft_divise(*iter, white_espace);
    // path = *iter + 1;

	vector<string> w_o_r_d = ft_divise(*iter, white_espace);

    type_request = w_o_r_d[0];
	Path = w_o_r_d[1];
	version_http = w_o_r_d[2];


    while(iter != request_divise.end())
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
         
            // if(First_line.size() != 3)
            // {
            //     break ;
            // }else{
                // server and browser exchange meta information about the document via the HTTP header.
                request_headers.insert(pair<string,string>("Host", First_line[1]));
                request_headers.insert(pair<string,string>("Port",First_line[2]));
            //}
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
int Request::get_Status_code()
{
	return Status_Code;
}

void Request::set_Path(std::string path)
{
    this->Path = path;
}

void Request::set_Status_code(int code)
{
	this->Status_Code = code;
}
int Request::check_which_location_compatible()
{
	string path_navigate;
	path_navigate = Path;
	std::list<Location> locations = Servers->get_locations();
	this->Locations = NULL;
	if(locations.size() == 0)
	{
		Locations = NULL;
		return 0;
	}
	//std::set<Location>::iterator i1;
    while(path_navigate != "")
    {
        for(std::list<Location>::iterator i1 = locations.begin(); i1 != locations.end() ; i1++)
	    {
		    if((i1)->get_path() == path_navigate)
		    {
			    this->Locations = new Location(*i1);
			    return 1;
		    }
	    }
        size_t count = path_navigate.find_last_of("/");
        if(count == string::npos)
        {
            break ;
        }
        path_navigate = path_navigate.substr(0, count);
		// std::cout << "path_navigate-->" << path_navigate << endl;
		

    }
		path_navigate  = "/";
		for(std::list<Location>::iterator i1 = locations.begin(); i1 != locations.end() ; i1++)
	    {
		    if((i1)->get_path() == path_navigate)
		    {
			    this->Locations = new Location(*i1);
			   	return 1;
		    }
	    }
	// if(this->Locations == NULL)
		return 0;
}

int Request::check_request_with_config_file(const std::set<server*> &servers)
{

	string Host;
	int var = 0;
	unsigned int port = 0;
	string path_navigate;
	int indice = 0;
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
		// 	std::cout << "Host-->" << Host << endl;
		// std::cout << "here'''\n";
		Host = "";
		Status_Code = 400;
		std::cout << "Bad request\n";
		return 0;
	}
	// std::cout << "port->" << port << endl;
	// if i have in my request header server_name = localhost and there no port 
	if(request_headers.find("Port") != request_headers.end())
	{
		port = atoi(request_headers.find("Port")->second.c_str());
	}else if(Host != "localhost" && port != 0)
	{
		//port = 0;
		Status_Code = 400;
		std::cout << "Bad request : The server cannot or will not process the request\n";
		return 0;
	}
		// if i have in my request header server_name = localhost and there no port 

	if(Host ==  "localhost" && port == 0)
	{
		port = 80;
	}

	
	for(iter3 = servers.begin(); iter3 != servers.end(); iter3++)
	{
		if((*iter3)->get_port_listen() == port)
		{
			this->Servers = (*iter3);
			//break ;
		}
		set<string> server_names = (*iter3)->get_server_name();
		for(iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
		{
			if((((*iter2) == Host || *iter2 == "0.0.0.0")  && ((*iter3)->get_port_listen() == port)))
			{
				this->Servers = (*iter3);
			}
		}
		// if i have server_name in the config file

	}
	// std::cout << "host->" << Host << endl;
	// std::cout << "Port->" << port << endl;
	
	if(this->Servers == NULL)
	{
		std::cout << "No Server is compatible\n";
		return 0;
	}
	//Content-Length is specified and it does not match the length of the message-line, the message is either truncated, or padded with nulls to the specified length.

	//The Content-Length header indicates the size of the message body, in bytes, sent to the recipient.

	//Basically it is the number of bytes of data in the body of the request or response.
	// atoll() string to long long int
	// std::cout << "Servers->get_client_max_body_size() " << Servers->get_client_max_body_size()  << endl;
	if (Servers->get_client_max_body_size() != -1 && atoi(request_headers["Content-Length"].c_str()) > Servers->get_client_max_body_size())
	{
		std::cout << "Payload Too Large\n";
		std::cout << "413 Request Entity Too Large\n";
		Status_Code = 413;
	}


	var = check_which_location_compatible();
	if (var == 0)
	{
		return 0;
	}
	
	vector<std::string> method_allow = Locations->get_http_allow_method();
	std::cout << "to check allow-> " << endl;
	for(std::vector<std::string>::iterator test = method_allow.begin(); test != method_allow.end(); test++)
	{
		std::cout << *test << endl;
	}
	for (vector<string>::iterator iter_method = method_allow.begin(); iter_method != method_allow.end(); iter_method++)
	{
		if (*iter_method == type_request)
			indice = 1;
	}

	if(indice == 0)
	{
		std::cout << "Method not allowed\n";
		Status_Code = 405;
		return 0;
	}
	
	if (Locations->get_http_redirection() > 0)
		Status_Code = Locations->get_http_redirection();
		
	else if (type_request == "DELETE")
	{
		Status_Code = 200;
	}
	

	return 1;

}

std::string Request::path_of_file()
{
	string Path_in_request;
	string tmp_file;
	int file_des;
    // int value = 0;
    if(Locations == NULL || Servers == NULL)
    {
		std::cout << "There is no server or location\n";
        path_of_file_dm = "";
		return path_of_file_dm;
    }
	// if (Path.find("//") != string::npos)
	// {
	// 	std::cout << "403 Not found\n";
	// 	Status_Code = 404;
	// 	return "";
	// }
	// if (type_request == "DELETE" && Status_Code != 403)
	// {
	// 	Status_Code = 200;
	// 	path_of_file_dm = "";
	// 	return "";
	// }
	// if (Status_Code == 413)
	// {
	// 	std::cout << "Request entity is larger than limits defined by server||  so we cant parse our path\n";
	// 	return "";
	// }
	
	Path_in_request = Path; // in my case i have / 
	path_of_file_dm = Servers->get_root();

    // std::cout << "server root->" << Servers->get_root() << endl;
    // std::cout << "Location root->" << Locations->get_root() << endl;
	//if(strcmp(Path_in_request, "/") == 0)
	if (Path_in_request.compare("/") == 0)
	{
		
		if (Locations && Locations->get_index().length())
			Path_in_request += '/' + Locations->get_index();
		else
			Path_in_request += '/' + Servers->get_index();
        // value = 1;
	}
	//return Path_in_request;
	//The function returns the index of the first occurrence of the sub-string.
	if (Path_in_request.find(Locations->get_path()) == 0)
	{
		
		Path_in_request = Path_in_request.substr(Locations->get_path().length());
		// std::cout << "path_request here -->" << Path_in_request << endl;
        if(is_directory(path_of_file_dm + Locations->get_root()))
        {
            path_of_file_dm += Locations->get_root();
			// std::cout << "path_of_file here?->" << path_of_file_dm << endl;
        }else
		{
			path_of_file_dm = path_of_file_dm + '/' + Locations->get_root();
		}
            
		
		// std::cout << "path->" << path_of_file_dm << endl;
	}
	//std::cout << "after\n";
	if(Path_in_request.length() == 0)
	{
		Path_in_request = Path;
		if (Locations && Locations->get_index().length())
			Path_in_request  += '/' + Locations->get_index();
		else
			Path_in_request  += '/' + Servers->get_index();

	}
	if(is_directory(path_of_file_dm + Path_in_request))
	{
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
	// std::cout << "tmp-->" << tmp_file << endl;
    // if(value == 0)
    // {
    //     std::cout << "yes\n";
    //     if (Locations && Locations->get_index().length())
	// 		tmp_file  += '/' + Locations->get_index();
	// 	else
	// 		tmp_file  += '/' + Servers->get_index();
    // }
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
    std::cout << "path hereee-->" << path_of_file_dm << endl;
    return path_of_file_dm;

}




std::string	Request::check_error_page(int error_code)
{
	if (Servers && Servers->get_error_pages().size() && Servers->get_error_pages().find(error_code) != Servers->get_error_pages().end() && Servers->get_error_pages()[error_code].size())
	{
		string file_page = Servers->get_root() + '/' + Servers->get_error_pages()[error_code];
		ifstream error_page(file_page.c_str(), ofstream::in);
		if (!error_page || !error_page.is_open() || !error_page.good())
		{
			std::cout << "This error_page dont exist\n";
			return (0);
		}
		error_page.close();
		return (Servers->get_root() + Servers->get_error_pages().find(error_code)->second);
	}
	else
	{
		stringstream str_data;
		str_data << error_code;

		return ("default_error/" + str_data.str() + ".html");
	}
		
}


int Request::get_indice()
{
	
	if(Status_Code == 0)
	{
		Status_Code = 200; //OK
	}else if (Status_Code == 400 || Status_Code == 403 || Status_Code == 404 || Status_Code == 413)
	{
		path_of_file_dm = check_error_page(Status_Code);
		return 0;
	}
	if (is_directory(path_of_file_dm))
	{
		if (path_of_file_dm[path_of_file_dm.size() - 1] == '/' && Locations->get_autoindex())
		{
			Status_Code = 200;
			return 1;
		}
		else
		{
			Status_Code = 403;
			std::cout << "The client does not have the access right to the content\n";
			path_of_file_dm = check_error_page(403);
		}
	}
	
	
	
	return 0; 
}

std::string Request::get_request_header(std::string name)
{
	if (request_headers.find(name) != request_headers.end())
		return request_headers[name];
	return "";
}


map<unsigned int, string> Request::Status_codes_means(void)
{
	map<unsigned int, string> code_stat;
	   code_stat.insert(std::pair<unsigned int, std::string>(200, "200 OK"));
	   code_stat.insert(std::pair<unsigned int, std::string>(203, "303 See Other"));
	   code_stat.insert(std::pair<unsigned int, std::string>(302, "302 Found"));
	   code_stat.insert(std::pair<unsigned int, std::string>(400, "400 Bad Request"));
	   code_stat.insert(std::pair<unsigned int, std::string>(403, "403 Forbidden"));
	   code_stat.insert(std::pair<unsigned int, std::string>(404, "404 Not Found"));
	   code_stat.insert(std::pair<unsigned int, std::string>(405, "405 Method Not allow"));
    	
		return code_stat ;
}

int Request::check_cgi()
{
	// int count_pos;
	count_pos = 0;
	//int value = 0;
	map<std::string, std::string> cgi = Servers->get_cgis();
	std::map<std::string, std::string>::iterator iter_cgi;

	for(iter_cgi = cgi.begin(); iter_cgi != cgi.end(); iter_cgi++)
	{
		//value = 1;
		count_pos = path_of_file_dm.find(iter_cgi->first);
		if(count_pos != string::npos)
		{
			return count_pos;
		}

	}
	return count_pos;
}

void Request::cgi_start()
{
	std::string extention_name = path_of_file_dm.substr(count_pos);

	std::cout << "extention_name-->" << extention_name << endl;
	pid_t pid = fork();
	if(pid < 0)
	{
		std::cout << "fork failed\n";
		exit(0);
	}else if(pid == 0)
	{
		std::vector<std::string> enverment;
		enverment.push_back("REQUEST_METHOD="+type_request);
		enverment.push_back("SCRIPT_NAME="+ path_of_file_dm);
		enverment.push_back("REDIRECT_STATUS=200");
		enverment.push_back("GATEWAY_INTERFACE=cgi/1.1");
		enverment.push_back("SERVER_PROTOCOL="+ version_http);
		if(type_request == "GET")
		{
			enverment.push_back("QUERY_STRING="+ path_of_file_dm);
			enverment.push_back("CONTENT_LENGTH=0");
		}else if(type_request == "SET")
		{
			enverment.push_back("REQUEST_METHOD="+type_request);
			if(Status_Code == 314)
				enverment.push_back("CONTENT_LENGTH=0");
			else
				enverment.push_back("CONTENT_LENGTH=0");
		}



	}
}




