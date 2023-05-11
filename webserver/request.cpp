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
#include <sys/wait.h>


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
	if (this->Locations != 0)
		delete(this->Locations);
}
void Request::Parcing_request(std::string buffer)
{
	vector<string> request_divise = ft_divise(buffer, "\r\n");

    vector<string>::iterator iter = request_divise.begin();
   

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
            // std::cout << "empty line\n";
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

// Here for POST request

/******* application/x-www-form-urlencoded − This is the standard method most forms use in simple scenarios.*/

/******** mutlipart/form-data − This is used when you want to upload binary data in the form of files like image, word file etc.*/


/*****enctype='multipart/form-data' means that no characters will be encoded. that is why this type is used while uploading files to server.
So multipart/form-data is used when a form requires binary data, like the contents of a file, to be uploaded*/

/*****Set the method attribute to POST because file content can't be put inside a URL parameter using a form.

Set the value of enctype to multipart/form-data because the data will be split into multiple parts, one for each file plus one for the text of the form body that may be sent with them.*/



	// if(request_headers.find("Content-Length") != request_headers.end() )
	// {
	// 	request_headers.insert(pair<string, string>("Body", request_divise.back()));
	// }
	
}	

void Request::ADD_body(std::string buffer)
{
	std::cout << "body befaure :" << request_headers["body"] << endl;
	request_headers["body"] += std::string(buffer, buffer.size());
	// request_headers["body"].
	// for (size_t i = 0; i < buffer.size(); i++)
	// 	request_headers["body"].push_back(buffer[i]);
	// request_headers["body"] += buffer;
	std::cout << "body after:" << request_headers["body"] << endl;
	//request_headers.insert(pair<string, string>("Body", buffer.c_str()));
	// std::cout << "so lets check body now -->" << request_headers["body"] << endl;
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
   
        for(std::list<Location>::iterator i1 = locations.begin(); i1 != locations.end() ; i1++)
	    {
		    if((i1)->get_path() == path_navigate)
		    {
			    this->Locations = new Location(*i1);
			    return 1;
		    }
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
	
		Host = "";
		Status_Code = 400;
		std::cout << "Bad request\n";
		return 0;
	}
	// if i have in my request header server_name = localhost and there no port 
	if(request_headers.find("Port") != request_headers.end())
	{
		port = atoi(request_headers.find("Port")->second.c_str());
	}else if(Host != "localhost" && port != 0)
	{
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

	}

	
	if(this->Servers == NULL)
	{
		std::cout << "No Server is compatible\n";
		return 0;
	}
	//Content-Length is specified and it does not match the length of the message-line, the message is either truncated, or padded with nulls to the specified length.

	//The Content-Length header indicates the size of the message body, in bytes, sent to the recipient.

	//Basically it is the number of bytes of data in the body of the request or response.
	// atoll() string to long long int
	std::cout << "Servers->get_client_max_body_size() " << Servers->get_client_max_body_size()  << endl;
	if (Servers->get_client_max_body_size() != -1 && atoi(request_headers["Content-Length"].c_str()) > Servers->get_client_max_body_size())
	{
		std::cout << "Payload Too Large\n";
		std::cout << "413 Request Entity Too Large\n";
		Status_Code = 413;
		return 0;
	}


	var = check_which_location_compatible();
	if (var == 0)
	{
		return 0;
	}
	// check uploading file..
	// should add just multipart Content-type
	if(request_headers["body"] != "")
	{
		// char *body_final;
		std::vector<string> vect_body;
		if(Locations->get_upload_enable() == 1)
		{
			string body_final;
			// get our body
			vector<string> body_divise = ft_divise(request_headers["body"], "\n");
			vector<string>::iterator iter = body_divise.begin() + 1;
			vector<string> w_o_r_d = ft_divise(*iter, ";");
			// std::cout <<"words->" << w_o_r_d[0] << endl; 
			// std::cout <<"words->" << w_o_r_d[1] << endl;
			// std::cout <<"words->" << w_o_r_d[2] << endl;
			vector<string>name_file = ft_divise(w_o_r_d[2], "\"");
			std::fstream myFile(name_file[1], std::ios::in | std::ios::out | std::ios::trunc);
			// vect_body = request_headers["body"];
			//std::map<string, string>::iterator iter = request_headers.begin() + 1;
			// for(std::map<string, string>::iterator iter = request_headers.begin(); iter != request_headers.end(); iter++)
			// {
			// 	vect_body.push_back(*iter);
			// }
			// for(std::vector<string>::iterator iterVect = vect_body.begin(); iterVect != vect_body.end(); iterVect++)
			// {
			// 	std::cout << "element-->" << *iterVect << endl;
			// }

			// std::cout << "request_body-->" << request_headers["body"][144] << endl;
			// std::cout << "size-->" << request_headers["body"].size() << endl;
			// std::cout << "position-->" << request_headers["body"].find_first_of("%");
			size_t pos = request_headers["body"].find_first_of("%");
			while(pos != request_headers["body"].size())
			{
				request_headers["upload"].push_back(request_headers["body"][pos]);
				pos++;
			}
			
			 myFile << request_headers["upload"] << endl;
		
			// myFile << request_headers["body"] << endl;
		}
	}
	
	vector<std::string> method_allow = Locations->get_http_allow_method();
	// std::cout << "to check allow-> " << endl;
	// for(std::vector<std::string>::iterator test = method_allow.begin(); test != method_allow.end(); test++)
	// {
	// 	std::cout << *test << endl;
	// }
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
	//int file_des;
    if(Locations == NULL || Servers == NULL)
    {
		std::cout << "There is no server or location\n";
        path_of_file_dm = "";
		return path_of_file_dm;
    }
	if (Path.find("//") != string::npos)
	{
		std::cout << "403 Not found\n";
		Status_Code = 404;
		return "";
	}
	// if (type_request == "DELETE" && Status_Code != 403)
	// {
	// 	Status_Code = 200;
	// 	path_of_file_dm = "";
	// 	return "";
	// }
	if (Status_Code == 413)
	{
		std::cout << "Request entity is larger than limits defined by server||  so we cant parse our path\n";
		return "";
	}
	
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
		
		path_of_file_dm = path_of_file_dm + "/" + Locations->get_root();
	
	}
	
	if(is_directory(path_of_file_dm + Path_in_request))
	{
		tmp_file = path_of_file_dm + Path_in_request + "/";
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
	// file_des = open(tmp_file.c_str(),O_RDONLY);
	// if(tmp_file[tmp_file.size() - 1] == '/' && file_des <= 0)
	// {
	// 	std::cout << "failed or what\n";
	// 	path_of_file_dm = Servers->get_root() + '/';
	// }
	// // else
	 path_of_file_dm = tmp_file;

	// close(file_des);
	std::size_t found = path_of_file_dm.find("//");
	if(found != std::string::npos)
	{
		path_of_file_dm.replace(found, 2 ,"/");
	}
    std::cout << "path hereee-->" << path_of_file_dm << endl;
    return path_of_file_dm;

}




std::string	Request::error_pages(int error_code)
{
	if (Servers && Servers->get_error_pages().size() && Servers->get_error_pages().find(error_code) != Servers->get_error_pages().end() && Servers->get_error_pages()[error_code].size())
	{
		std::cout << "yes error_page\n";
		string file_page = Servers->get_root() + '/' + Servers->get_error_pages()[error_code];
		return (Servers->get_root() + Servers->get_error_pages().find(error_code)->second);
	}
	else
	{
		stringstream str_data;
		str_data << error_code;

		return (Servers->get_root() + "/default_error/" + str_data.str() + ".html");
	}
		
}


int Request::check_auto_index(std::string path_access)
{
	std::cout << "check value auto-->" << Locations->get_autoindex() << endl;
std::cout << "path in auto index-->" << path_access << endl;
	if (is_directory(path_access))
	{
		if (path_access[path_access.size() - 1] == '/' && Locations->get_autoindex() == "on")
		{
			Status_Code = 200;
			return 1;
		}
		else
		{
			Status_Code = 403;
			std::cout << "The client does not have the access right to the content\n";
			return 2;
		}
	}
	
	
	
	return 0; 
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


char ** Request::get_the_path(std::string extention_name)
{
	// firstly get the current directory
	/**** These functions return a null-terminated string containing an
       absolute pathname that is the current working directory of the
       calling process.*/
	std::string cgi_path;
	char **argument;
	char *path = getcwd(NULL, 0);
	string path_actuel = string(path);
	free(path);
	// std::vector<std::string>path_final;
	// find() returns an iterator or a constant iterator that refers to the position where the key is present in the map.
	if(Servers->get_cgis().find(extention_name) != Servers->get_cgis().end())
	{
		cgi_path = Servers->get_cgis().find(extention_name)->second;
	}
	// check if this path exist or not

	int fd_cgi = open(cgi_path.c_str(),O_RDONLY );
	if(fd_cgi <= 0)
	{
		std::cout << "Cgi file open error\n";
		return 0;
	}
	std::vector<std::string> path_final;
	path_final.push_back(cgi_path);
	path_final.push_back(path_actuel + "/" + path_of_file_dm.substr(0, path_of_file_dm.find_first_of('?', 0)));
	//std::cout << "path_final[1]-->" << path_final[1] << endl; 
	//std::cout << "path_final size-->" << path_final.size() << endl;
	// put our vector in char ** variable

	argument = static_cast<char **>(malloc(sizeof(char *) * (path_final.size() + 1)));

	for(size_t i = 0; i < path_final.size(); i++)
	{
		argument[i] = ft_strdup(path_final[i]);
	}
	argument[path_final.size()] = 0;




	return argument;
}

char *Request::ft_strdup(string path)
{
	char *var = static_cast<char*>(malloc(sizeof(char) * (path.size() + 1)));

	unsigned int i = 0;
	while (i < path.size())
	{
		var[i] = path[i];
		i++;
	}
	var[i] = 0;
	return var;
}

void Request::cgi_start(std::string &test)
{
	// int *status = NULL;
	// int options;
	char **argv;
	char **env;
	
	std::string body;
	std::string extention_name = path_of_file_dm.substr(count_pos);
	char *path = getcwd(NULL, 0);
	string path_actuel = string(path);
	free(path);
	std::cout << "extention_name-->" << extention_name << endl;

	int fd_pipe[2];

	if(pipe(fd_pipe) == -1)
	{
		std::cout << "Error pipe\n";
		exit(0);
	}
	pid_t pid = fork();
	if(pid < 0)
	{
		std::cout << "fork failed\n";
		exit(0);
	}else if(pid == 0)
	{
		std::cout<< "shild process\n";
		std::vector<std::string> enverment;
		enverment.push_back("REQUEST_METHOD="+type_request);
		enverment.push_back("SCRIPT_FILENAME="+ path_actuel + "/" + path_of_file_dm);
		enverment.push_back("REDIRECT_STATUS=");
		enverment.push_back("GATEWAY_INTERFACE=cgi/1.1");
		enverment.push_back("SERVER_PROTOCOL="+ version_http);
		if(type_request == "GET")
		{
			std::cout << "Get ofcourse\n";
			// here for example php_website/index.php
			enverment.push_back("QUERY_STRING="+ path_of_file_dm.substr(path_of_file_dm.find_first_of('?') + 1));
		}else if(type_request == "POST")
		{
			if(Status_Code == 314)
				enverment.push_back("CONTENT_LENGTH=0");
			else
				enverment.push_back("CONTENT_LENGTH=0");
		}

		env = static_cast<char **>(malloc(sizeof(char *) * (enverment.size() + 1)));
		for(size_t k =0; k < enverment.size() ; k++)
		{
			env[k] = ft_strdup(enverment[k]);
		}
		env[enverment.size()] = 0;
		argv = get_the_path(extention_name);
		close(fd_pipe[0]);
		if(dup2(fd_pipe[1], 1) == -1)
		{
			std::cout<< "Error dup\n";
			exit(0);
		}

		// std::cout << "argv[0]-->" << argv[0] << endl;
		// std::cout << "argv[1]-->" << argv[1] << endl;
		if(execve(argv[0], argv, env) < 0)
		{
			std::cout << "execve error\n";
			Status_Code = 404;
		}
	}else
	{
		close(fd_pipe[1]);
		wait(0);
		std::cout << "here parent\n";
		char reading;
		while (read(fd_pipe[0], &reading, 1) > 0)
			body = body + reading;
		//std::cout << "reading-->" << reading << endl;
		//std::cout << "body ==" << body << endl;
		vector<string> header = ft_divise(body, "\r");	
		test = header[3];
		// std::cout << "test-->" << test << endl;
		close(fd_pipe[0]);
		
	}
	
		
		
}


string &Request::get_request_header(string element)
{
		return request_headers[element];
	// if (request_headers.find(element) != request_headers.end())
	// 	return request_headers[element];
	// else
	// 	return "";
}


void Request::auto_index(std::string &str, std::string path_access)
{
	stringstream auto_index;
	//passed_cgi = true;
	auto_index << "	<html lang=\"en\">\n\
					<body style=\"background-color: yellow; color: black;\">\n\
					<div style=\"display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;\">\n\
						<h1>Index of</h1>\n";
	auto_index << Path;
	DIR *directory;
	struct dirent *entry;
	//The opendir() function opens a directory stream corresponding to the directory named by the dirname argument

	//Upon successful completion, opendir() returns a pointer to an object of type DIR
	if ((directory = opendir(path_access.c_str())) != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
		{
			// It returns a null pointer upon reaching the end of the directory stream
			string our_link = entry->d_name;
			// std::cout << "link here-->" << our_link << endl;
			if (is_directory(path_access + '/' + our_link))
			{
				our_link += '/';
			}	
			auto_index << "<p><a href=\"" << our_link << "\" class=\"active\">" << our_link << "</a></p>\n";
		}
		closedir (directory);
	}
	else
	{
		std::cout << "Open Dir error\n";
		exit(0);
	}
	auto_index << "	</div>\n\
					</body>\n\
					</html>";
	Status_Code = 200;
	str = auto_index.str();
}