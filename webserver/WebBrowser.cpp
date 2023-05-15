/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebBrowser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:23:29 by souchen           #+#    #+#             */
/*   Updated: 2023/04/06 14:23:30 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/WebBrowser.hpp"
#include "../headers/server.hpp"
#include "../headers/request.hpp"
#include "../headers/response.hpp"
#include <fcntl.h>


#define BUFFUR_SIZE 4096

WebBrowsers::WebBrowsers(std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request(0),indice(0)
{
	
	std::cout << "Connection......\n";


	
}
WebBrowsers::~WebBrowsers()
{
	std::cout << "Destructer client---> Client disconnected\n";
	if (file_descriptor > 0)
		close(file_descriptor);
	// if (request != 0)
	// {
	// 	delete request;
	// 	request = 0;
	// }

}

/*** if the server receives a request for a webpage from a client,				  **/
/*** the server will parse the request and pass it to a Response object which 	  **/
/*** will fetch the contents of the webpage and construct the HTTP response 	  **/
/*** with the HTML content in the message body and the appropriate headers,		  **/
/***  such as the Content-Type and Content-Length headers.      				 ***/



int WebBrowsers::Read_request()
{

	//std::cout << "read_request\n";
		int recv_s;
		char buffer[BUFFUR_SIZE];
		// int test = 0;
		//std::string read_buffer;
		value = 0;
		
		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/

		/*******This call returns the length of the incoming message or data. If a datagram packet is too long to fit in the supplied buffer, datagram sockets discard excess bytes. If data is not available for the socket socket, and socket is in blocking mode, the recv() call blocks the caller until data arrives. If data is not available and socket is in nonblocking mode, recv() returns a -1 and sets the error code to EWOULDBLOCK.*/
		// std::cout << "test\n";
		// std::cout << test << endl;
		recv_s = recv(file_descriptor, buffer,BUFFUR_SIZE, 0 );
		std::cout << "recv_s-->" << recv_s << endl;
		// std::cout << "size_buffer-->" << strlen(buffer) << endl;
		std::cout << "buffer -->\n";
		std::cout << buffer << endl;
		// std::cout << "octet-->" << recv_s << endl; 
		if(recv_s < 0)
		{
			std::cout << "No message are available to be received\n";
			//value = 1;
			return 2;
		}else if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			//value = 1;
			return 2;
		}
	
		if(request == NULL)
		{
			read_buffer = read_buffer + string(buffer, recv_s);
			std::cout << "read_buffer:\n";
			std::cout << read_buffer << endl;
			// std::cout << "recv_s-->" << recv_s << endl;
			size_t p2 = read_buffer.find("\\r\\n\\r\\n");
			if(p2 != std::string::npos)
			{
				std::cout << "true there is a -->" << endl;
			}
			// size_t p = read_buffer.find("//n");
			// if(p != std::string::npos)
			// {
			// 	std::cout << "true there is a -->" << endl;
			// }
			//std::cout << "pos-->" << p << endl;
			if(request == NULL && recv_s <= BUFFUR_SIZE && (read_buffer.find("\r\n\r\n") != std::string::npos || p2 != std::string::npos))
			{
				
				std::cout << "parse request\n";
				// get all the request with body ou without body
				request = new Request(read_buffer);
				// if(read_buffer.find("Content-Length: ") == std::string::npos)
				// {
				// 		if(read_buffer.find("Transfer-Encoding: chunked") != std::string::npos)
				// 		{

				// 		}
				// }
				
				
				size_t pos = request->get_content_type().find("application");
				// if(request->get_transfer_encoding().find("chunked") != std::string::npos)
				// {
				// 	std::cout << "just wait\n";
				// }
				
				if (request->get_type_request() == "GET" || request->get_type_request() == "DELETE")
					value = 1;
				else if (request->get_type_request() == "POST" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
					value = 1;
				else if(request->get_type_request() == "POST" && pos != std::string::npos)
				{
					value = 1;
				}
			}
			//read_buffer.clear();
		}
		else if (request != NULL)
		{
			
			if(request->get_transfer_encoding().find("chunked") != std::string::npos)
			{
				read_buffer = read_buffer + buffer;
				std::cout << "read_buffer in chunked-->\n";
				std::cout << read_buffer << endl;
				if(EndChunked(read_buffer, "0\r\n\r\n") == 1)
				{
					std::cout << "chunked test\n";
					std::string header = read_buffer.substr(0, read_buffer.find("\r\n\r\n"));
					std::string chunks = read_buffer.substr(read_buffer.find("\r\n\r\n") + 4, read_buffer.size() - 1);
					std::string subchunk = chunk.substr(0,100);
					int			chunksize = strtol(subchunk.c_str(), NULL, 16);
					size_t		i = 0;
					while (chunksize)
					{
						i = chunks.find("\r\n", i) + 2;
						body += chunks.substr(i, chunksize);
						i += chunksize + 2;
						subchunk = chunks.substr(i, 100);
						chunksize = strtol(subchunk.c_str(), NULL, 16);
	
					}

				}
				
				

			}else{
				for(int i = 0; i < recv_s; i++)
				{
					request->get_request_header("body").push_back(buffer[i]);	
				}
			
				if (request->get_type_request() == "POST" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
					value = 1;	
			}
			
				
			
					
				
		}
	
		
			
	
		
	return value;
}


int WebBrowser::EndChunked(std::string &buffer, std::string &end_check)
{
	size_t	i = buffer.size();
	size_t	j = end_check.size();

	while (j > 0)
	{
		i--;
		j--;
		if (i < 0 || buffer[i] != end_check[j])
			return (0);
	}
	return (1);
}

int WebBrowsers::get_check_fd()
{
    return check_fd;
}

struct sockaddr* WebBrowsers::get_address_client(void)
{
    return (struct sockaddr*)(&address_client);
}

int WebBrowsers::get_file_descriptor()
{
    return file_descriptor;
}

int WebBrowsers::get_value()
{
	return value;
}
int WebBrowsers::get_indice()
{
	return indice;
}

// setters

void WebBrowsers::set_file_descriptor(int fd)
{
    file_descriptor = fd;
}


// some used functions

void WebBrowsers::check_request()
{

	request->check_request_with_config_file(servers);
	Locations = request->get_location();

}

void WebBrowsers::ThePath_of_acces_file()
{
	autoindex = 0;
	path_access = request->path_of_file();
	if(path_access != "")
		autoindex = request->check_auto_index(path_access);

}
void WebBrowsers::check_error_page()
{
	if(request->get_Status_code() == 0)
	{
		request->set_Status_code(200);
	}
	if(request->get_Status_code() == 400 || request->get_Status_code() == 403 || request->get_Status_code() == 404 || request->get_Status_code() == 413)
	{
		path_access = request->error_pages(request->get_Status_code());
	}
	
	

}
void WebBrowsers::prepareResponse()
{
	//int status;
	int code_status;
	int value_status = 0;
	int delete_indice = 0;
	int count;
	send_byte = 0;
	std::string new_path_access = "";
	
	new_path_access = path_access.substr(0, path_access.find_first_of('?',0));
	// std::cout << "new_path-->" << new_path_access << endl;
	check_error_page();

	ifstream file_check(new_path_access.c_str(), ofstream::in);
	if(((!file_check || !file_check.is_open() || !file_check.good()) ) && Locations->get_http_redirection() == 0)
	{
		request->set_Status_code(404);
		new_path_access = request->error_pages(request->get_Status_code());
		file_check.close();
	}
	if(autoindex == 1)
	{
		value_status = 3;
		file_check.close();
	}else if(autoindex == 0)
	{
		count = request->check_cgi();
		if(count > 0)
			value_status = 2;
		file_check.close();
	}

	if(request->get_type_request() == "DELETE")
	{
		delete_indice = 2;
	}
	
	// status = request->get_indice();
	code_status = request->get_Status_code();
	map<unsigned int, string> map_Codestatus = request->Status_codes_means();
	file_file_descriptor = open(new_path_access.c_str(), O_RDONLY);
	response Response;
	if(value_status == 0 && delete_indice == 0)
	{
		response_buffer = Response.response_header(0 , 0, new_path_access, code_status, map_Codestatus, Locations);
		indice = 2;
		delete request;
		request = 0;

	}else if(value_status == 2 && delete_indice == 0)
	{
		std::string body;
		request->cgi_start(body);
		response_buffer = Response.response_header(body.size() ,1, new_path_access, code_status, map_Codestatus, Locations);
		response_buffer = response_buffer + body;
		file_file_descriptor = 0;
		indice = 2;
		delete request;
		request = 0;
	}else if(value_status == 3 && delete_indice == 0)
	{
		
		string str;
		request->auto_index(str,  new_path_access);
		response_buffer = Response.response_header(str.size() ,1, new_path_access, code_status, map_Codestatus, Locations);
		response_buffer = response_buffer + str;
		file_file_descriptor = 0;
		indice = 2;
		delete request;
		request = 0;
	}else if(delete_indice == 2)
	{
		request->delete_request();	
		response_buffer = Response.response_header(0 ,1, new_path_access, code_status, map_Codestatus, Locations);
		indice = 2;
		file_file_descriptor = 0;
		delete request;
		request = 0;

	}
}

void WebBrowsers::send_response()
{
	if(indice == 2)
	{
		send1();
	}else if(indice == 3)
	{
		send2();
	}
	
}

void WebBrowsers::send1()
{
	
	send(file_descriptor, response_buffer.c_str(), response_buffer.size(), 0);	
	response_buffer.clear();
	indice = 3;
	delete request;
	request = 0;

}

void WebBrowsers::send2()
{
	int fd;
	char 	buff[BUFFUR_SIZE];
	if(file_file_descriptor == 0)
	{
		delete request;
		value = 0;
		indice = 0;
		request = NULL;
		std::cout << "Sending file to client.....\n";
		return ;
	}
	fd = read(file_file_descriptor, buff, BUFFUR_SIZE);
	
	// std::cout << "fd = " << fd << endl;
	if(fd <= 0)
	{
		close(file_file_descriptor);
		delete request;
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request = NULL;
	}

	send(file_descriptor, buff, fd, 0);

	if (fd < BUFFUR_SIZE)
	{
		std::cout << "sendig file to client !\n";
		close(file_file_descriptor);
		delete(request);
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request = NULL;
	}
}



