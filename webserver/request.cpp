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
    std::cout << YELLOW << "Send a request\n";
}

Request::Request(std::string buffer):Locations(0),Status_Code(0),content_length_exist(0)
{
  
	Parcing_request(buffer);

}

// // destructer
Request::~Request()
{
	if (this->Locations != 0)
		delete(this->Locations);
	
}
void Request::Parcing_request(std::string buffer)
{
	std::vector<std::string> request_divise = ft_divise(buffer, "\r\n");

    std::vector<std::string>::iterator iter = request_divise.begin();
   

	std::vector<std::string> w_o_r_d = ft_divise(*iter, white_espace);
	if(buffer.size() != 0 && w_o_r_d.size() >=2) 
	{
		type_request = w_o_r_d[0];
		Path = w_o_r_d[1];
		if(Path.find("?") != std::string::npos)
			Path = Path.substr(0, Path.find_first_of('?',0));
	}
   


    while(iter != request_divise.end())
    {
        std::vector<std::string> First_line = ft_divise(*iter, ": ");
        std::vector<std::string>::iterator i = First_line.begin();

        if(First_line.size() < 2)
        {
            break ;
        }
        if(*i == "Host")
        {
            std::vector<std::string> split_Host = ft_divise(First_line[1], ":");
         
            // server and browser exchange meta information about the document via the HTTP header.
            request_headers.insert(std::pair<std::string,std::string>("Host", First_line[1]));
            request_headers.insert(std::pair<std::string,std::string>("Port",First_line[2]));
           
        }else
            request_headers.insert(std::pair<std::string, std::string>(First_line[0], First_line[1]));



        iter++;

    }
	// check content type
	size_t pos;
	if((pos = buffer.find("Content-Type: ")) != std::string::npos)
	{
		content_type = buffer.substr(pos, buffer.find('\n', pos));
		pos = content_type.find_first_of(": ") + 2;
		content_type = content_type.substr(pos, (content_type.find("\n", 0) - pos));
	}

	if(request_headers.count("Content-Length") > 0)
	{
		content_length_exist = 1;
		request_headers.insert(std::pair<std::string,std::string>("body",""));
	}
	// check chuncked request
	std::size_t count;
	if((count = buffer.find("Transfer-Encoding: ")) != std::string::npos)
	{
		
		transfer_encoding = buffer.substr(count, buffer.find('\n', count));
		count = transfer_encoding.find_first_of(": ") + 2;
		transfer_encoding = transfer_encoding.substr(count, (transfer_encoding.find("\n", 0) - count));
		
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
	std::string path_navigate;
	path_navigate = Path;

	std::list<Location> locations = Servers->get_locations();
	this->Locations = NULL;
	if(locations.size() == 0)
	{
		Locations = NULL;
		return 0;
	}
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
		if(count == std::string::npos)
		{
			break;
		}
		path_navigate = path_navigate.substr(0,count);
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

	std::string Host;
	int var = 0;
	unsigned int port = 0;
	std::string path_navigate;
	int indice = 0;

	path_navigate = Path;
	std::set<server*>::iterator const_iter1;
	std::set<std::string>::iterator iter2;
	std::set<server*>::iterator iter3;
	std::set<server*>::iterator iter4;
	this->Servers =  NULL;
	if(request_headers.find("Host") != request_headers.end())
	{
		Host = request_headers.find("Host")->second;
	}
	else 
	{
		Host = "";
		Status_Code = 400;
		return 0;
	}
	// if i have in my request header server_name = localhost and there no port 
	if(request_headers.find("Port") != request_headers.end())
	{
		port = atoi(request_headers.find("Port")->second.c_str());
	}
	// if i have in my request header server_name = localhost and there no port 
	if(Host ==  "localhost" && port == 0)
	{
		port = 80;
	}

	
	for(iter3 = servers.begin(); iter3 != servers.end(); iter3++)
	{
		// we can have two servers with the same port
		
			if((*iter3)->get_port_listen() == port)
			{
			
					this->Servers = (*iter3);
					break ;
				
			}
			std::set<std::string> server_names = (*iter3)->get_server_name();
			for(iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
			{
				if(((*iter2) == Host))
				{
					this->Servers = (*iter3);
				}
			}
	}
	
	

	if(this->Servers == NULL)
	{
		Status_Code = 400;
		return 0;
	}
	

	if (Servers->get_client_max_body_size() != -1  && atoi(request_headers["Content-Length"].c_str()) > Servers->get_client_max_body_size())
	{
		std::cout << RED <<"Payload Too Large\n";
		std::cout << BLUE << "413 Request Entity Too Large\n";
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
	if(request_headers["body"] != "" && request_headers["Content-Type"].find("multipart") != std::string::npos)
	{
		std::vector<std::string> vect_body;
		std::vector<std::string>name_file;
		std::vector<std::string> w_o_r_d;
		std::string path_doc;
		if(Locations->get_upload_enable() == 1)
		{
			std::cout << GREEN << "uploading......\n";
			std::string body_final;
			
			std::vector<std::string> body_divise = ft_divise(request_headers["body"], "\n");
			if(body_divise[1].find("filename") != std::string::npos)
			{
					w_o_r_d = ft_divise(body_divise[1], ";");
					name_file = ft_divise(w_o_r_d[2], "\"");
			
					path_doc = "/Users/souchen/Desktop/Myserver/website/upload-test/upload-doc/" + name_file[1];
					request_headers["body"] = request_headers["body"].substr(request_headers["body"].find("\n\r\n") + 3,request_headers["body"].size() - 1 );
					std::fstream myFile(path_doc, std::ios::in | std::ios::out | std::ios::trunc);
					myFile << request_headers["body"];
			}else
			{
				path_doc = "/Users/souchen/Desktop/Myserver/website/upload-test/upload-doc/data.txt";
				request_headers["body"] = request_headers["body"].substr(request_headers["body"].find("\n\r\n") + 3,request_headers["body"].size() - 1 );
				std::fstream myFile(path_doc, std::ios::in | std::ios::out | std::ios::trunc);
				myFile << request_headers["body"];
				
			}
				
			

	
			 
		
		}
	}
	
	std::vector<std::string> method_allow = Locations->get_http_allow_method();

	for (std::vector<std::string>::iterator iter_method = method_allow.begin(); iter_method != method_allow.end(); iter_method++)
	{
		if (*iter_method == type_request)
			indice = 1;
	}

	if(indice == 0)
	{
		Status_Code = 405;
		std::cout << RED << "Method not allowed\n";
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

	std::string Path_in_request;
	std::string tmp_file;
	if(Status_Code == 405)
	{
		Status_Code = 405;
		path_of_file_dm = "";
		return path_of_file_dm ;
	}
   	if(Status_Code == 400)
	{
		Status_Code = 400;
		path_of_file_dm = "";
		return path_of_file_dm ;
	}
	if (Status_Code == 413)
	{
		std::cout << RED << "Request entity is larger than limits defined by server\n";
		path_of_file_dm = "";
		return path_of_file_dm ;
	}
    
    if(Locations == NULL || Servers == NULL)
    {
		Status_Code = 400;
        path_of_file_dm = "";
		return path_of_file_dm;
    }

	
	Path_in_request = Path; // in my case i have / 
	
	path_of_file_dm = Servers->get_root();

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
		path_of_file_dm = path_of_file_dm + '/' + Locations->get_root();
	}
	
	if(is_directory(path_of_file_dm + Path_in_request))
	{
		tmp_file = path_of_file_dm + Path_in_request;
	}
	else
	{
		tmp_file = path_of_file_dm + '/' + Path_in_request;
	}

	if(is_directory(tmp_file) && tmp_file[tmp_file.length() - 1] != '/')
	{
	
		if(Locations->get_index().length())
		{
			tmp_file = tmp_file +  "/" + Locations->get_index();
		
		}
	}else if(is_directory(tmp_file) && tmp_file[tmp_file.length() - 1] == '/')
	{

		if(Locations->get_index().length())
		{

			tmp_file = tmp_file + Locations->get_index();
		}
	}

	if(is_directory(tmp_file) && tmp_file[tmp_file.length() - 1] != '/')
		tmp_file = tmp_file + '/';
	path_of_file_dm = tmp_file;

	 
	path_of_file_dm = tmp_file;

	std::size_t found = path_of_file_dm.find("//");
	if(found != std::string::npos)
	{
		path_of_file_dm.replace(found, 2 ,"/");
	}

	return path_of_file_dm;

}




std::string	Request::error_pages(int error_code)
{
	if (Servers && Servers->get_error_pages().size() && Servers->get_error_pages().find(error_code) != Servers->get_error_pages().end() && Servers->get_error_pages()[error_code].size())
	{
		std::string file_page = Servers->get_root() + '/' + Servers->get_error_pages()[error_code];
		std::ifstream file_error(file_page.c_str(), std::ofstream::in);
		if(((!file_error || !file_error.is_open() || !file_error.good()) ))
		{
			return ("website/404.html");

			file_error.close();
		}
		return (Servers->get_root() + Servers->get_error_pages().find(error_code)->second);
	}
	else
	{
		std::string file_page;
		std::stringstream str_data;
		str_data << error_code;
		if(Servers != NULL)
		{
			file_page = Servers->get_root() + "/default_error/" + str_data.str() + ".html";
			std::ifstream file_error(file_page.c_str(), std::ofstream::in);
			if(((!file_error || !file_error.is_open() || !file_error.good()) ))
			{
				return ("website/default_error/" + str_data.str() + ".html");
				file_error.close();
			}
			return (Servers->get_root() + "/default_error/" + str_data.str() + ".html");
		}
			return ("website/default_error/" + str_data.str() + ".html");
			

	}
		
}


int Request::check_auto_index(std::string path_access)
{
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
			std::cout << RED <<"index off --->The client does not have the access right to the content\n";
			return 2;
		}
	}
	
	
	
	return 0; 
}



std::map<unsigned int, std::string> Request::Status_codes_means(void)
{
	std::map<unsigned int, std::string> code_stat;
	   code_stat.insert(std::pair<unsigned int, std::string>(100, "contenue"));
	   code_stat.insert(std::pair<unsigned int, std::string>(200, "200 OK"));
	   code_stat.insert(std::pair<unsigned int, std::string>(201, "201 Created"));
	   code_stat.insert(std::pair<unsigned int, std::string>(202, "202 Accepted"));
	   code_stat.insert(std::pair<unsigned int, std::string>(203, "203 Non-Authoritative Information"));
	   code_stat.insert(std::pair<unsigned int, std::string>(204, "204 No Content"));
	   code_stat.insert(std::pair<unsigned int, std::string>(205, "205 Reset content"));
	   code_stat.insert(std::pair<unsigned int, std::string>(300, "300 Multiple choices"));
	   code_stat.insert(std::pair<unsigned int, std::string>(301, "301 Moved Permanently"));
	   code_stat.insert(std::pair<unsigned int, std::string>(302, "302 Found"));
	   code_stat.insert(std::pair<unsigned int, std::string>(303, "303 see other"));
	   code_stat.insert(std::pair<unsigned int, std::string>(304, "304 used proxy"));
	   code_stat.insert(std::pair<unsigned int, std::string>(306, "306 Unused"));
	   code_stat.insert(std::pair<unsigned int, std::string>(307, "307 Temporary Redirect"));
	   code_stat.insert(std::pair<unsigned int, std::string>(400, "400 Bad Request"));
	   code_stat.insert(std::pair<unsigned int, std::string>(403, "403 Forbidden"));
	   code_stat.insert(std::pair<unsigned int, std::string>(404, "404 Not Found"));
	   code_stat.insert(std::pair<unsigned int, std::string>(405, "405 Method Not allow"));
	   code_stat.insert(std::pair<unsigned int, std::string>(405, "500 Internal Server Error"));
	   	code_stat.insert(std::pair<unsigned int, std::string>(413, "413 Payload Too Large"));
		return code_stat ;
}

int Request::check_cgi()
{
	count_pos = 0;
	std::map<std::string, std::string> cgi = Servers->get_cgis();
	std::map<std::string, std::string>::iterator iter_cgi;

	for(iter_cgi = cgi.begin(); iter_cgi != cgi.end(); iter_cgi++)
	{
		count_pos = path_of_file_dm.find(iter_cgi->first);
		if(count_pos != std::string::npos)
		{
			return count_pos;
		}

	}
	count_pos = 0;

	return count_pos;
}


char ** Request::get_the_path(std::string extention_name)
{

	std::string cgi_path;
	char **argument;
	char *path = getcwd(NULL, 0);
	std::string path_actuel = std::string(path);
	free(path);

	if(Servers->get_cgis().find(extention_name) != Servers->get_cgis().end())
	{
		cgi_path = Servers->get_cgis().find(extention_name)->second;
	}
		
	int fd_cgi = open(cgi_path.c_str(),O_RDONLY );
	if(fd_cgi <= 0)
	{
		std::cout << "Cgi file open error\n";
		Status_Code = 500;
		return 0;
	}
	std::vector<std::string> path_final;
	path_final.push_back(cgi_path);
	path_final.push_back(path_actuel + "/" + path_of_file_dm.substr(0, path_of_file_dm.find_first_of('?', 0)));


	argument = static_cast<char **>(malloc(sizeof(char *) * (path_final.size() + 1)));
	if(argument == NULL)
	{
		free(argument);
		exit(1);
	}
		
	for(size_t i = 0; i < path_final.size(); i++)
	{
		argument[i] = ft_strdup(path_final[i]);
	}
	argument[path_final.size()] = 0;




	return argument;
}

char *Request::ft_strdup(std::string path)
{
	char *var = static_cast<char*>(malloc(sizeof(char) * (path.size() + 1)));
	if(var == NULL)
	{
		free(var);
		exit(1);
	}

	unsigned int i = 0;
	while (i < path.size())
	{
		var[i] = path[i];
		i++;
	}
	var[i] = 0;
	return var;
}

std::string Request::cgi_start(std::string &body_final)
{
	char **argv;
	char **env;
	std::string headers;
	
	std::string body;
	std::string extention_name = path_of_file_dm.substr(count_pos);
	char *path = getcwd(NULL, 0);
	std::string path_actuel = std::string(path);
	free(path);

	int fd_pipe[2];
	int post_pipe[2];

	if(pipe(fd_pipe) == -1)
	{
		std::cout << "Error pipe\n";
		exit(0);
	}
	if(type_request == "POST")
	{
		if(pipe(post_pipe) == -1)
		{
			std::cout << "Error pipe\n";
			exit(0);
		}
	}
	pid_t pid = fork();
	if(pid < 0)
	{
		std::cout << RED << "Fork failed\n";
		exit(0);
	}else if(pid == 0)
	{
		std::vector<std::string> enverment;
		enverment.push_back("REQUEST_METHOD="+type_request);
		enverment.push_back("SCRIPT_FILENAME="+ path_actuel + "/" + path_of_file_dm.substr(0,path_of_file_dm.find_first_of('?',0)));
		enverment.push_back("REDIRECT_STATUS=200");
		enverment.push_back("GATEWAY_INTERFACE=cgi/1.1");
		enverment.push_back("SERVER_PROTOCOL="+ version_http);
		if (request_headers["Cookie"] != "")
			enverment.push_back("HTTP_COOKIE="+ request_headers["Cookie"]);
		if(type_request == "GET")
		{
			enverment.push_back("QUERY_STRING="+ path_of_file_dm.substr(path_of_file_dm.find_first_of('?') + 1));
			extention_name = extention_name.substr(0,extention_name.find_first_of('?'));
		}
		else if(type_request == "POST")
		{
			enverment.push_back("CONTENT_TYPE="+content_type);
			if(Status_Code == 413)
				enverment.push_back("CONTENT_LENGTH=0");
			else
				enverment.push_back("CONTENT_LENGTH="+request_headers["Content-Length"]);
		}
		env = static_cast<char **>(malloc(sizeof(char *) * (enverment.size() + 1)));
		if(env == NULL)
		{
			free(env);
			exit(1);
		}
		for(size_t k =0; k < enverment.size() ; k++)
		{
			env[k] = ft_strdup(enverment[k]);
		}
		env[enverment.size()] = 0;
		argv = get_the_path(extention_name);
	
		if(type_request == "POST" && Status_Code != 413)
		{
			close(post_pipe[1]);
			if (dup2(post_pipe[0], 0) == -1)
			{
				std::cout<< RED << "Dup2 error\n";
				exit(0);
			}
		}
		close(fd_pipe[0]);
		if(dup2(fd_pipe[1], 1) == -1)
		{
			std::cout<< RED << "Dup2 Error dup\n";
			exit(0);
		}

		
		if(execve(argv[0], argv, env) < 0)
		{
			std::cout << RED <<"execve error\n";
			Status_Code = 500;
		}
	}else
	{
		if (type_request == "POST" &&  Status_Code != 413)
		{
			
		 	close(post_pipe[0]);
		
			if (write(post_pipe[1], request_headers["body"].c_str(), request_headers["body"].size()) < 0)
				std::cout << RED<< "write error\n";
		
			close(post_pipe[1]);
		}
		close(fd_pipe[1]);
		wait(0);
		char reading;
		while (read(fd_pipe[0], &reading, 1) > 0)
		{
			
			body = body + reading;
		}
	
			headers = body.substr(0,body.find("\r\n\r\n"));
			body_final = body.substr(body.find("\r\n\r\n"), body.size());
		

		
		
		close(fd_pipe[0]);
		
	}
	return headers;
	
		
		
}


std::string &Request::get_request_header(std::string element)
{
		return request_headers[element];
	
}


void Request::auto_index(std::string &str, std::string path_access)
{
	std::stringstream auto_index;
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
			std::string our_link = entry->d_name;
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

Location *Request::get_location()
{
	return Locations;
}

void Request::delete_request(std::string &path)
{
	
	Status_Code = 200;
	if(remove(path_of_file_dm.c_str()) == -1)
	{
		std::cout << RED << "Remove failed\n";
		Status_Code = 404;
	}

	if(Status_Code == 404)
	{
		path = error_pages(Status_Code);
	}
	
	
}

std::string Request::get_content_type()
{
	return content_type;
}

std::string Request::get_transfer_encoding()
{
	return transfer_encoding;
}
int Request::get_content_length_exist()
{
	return content_length_exist;
}