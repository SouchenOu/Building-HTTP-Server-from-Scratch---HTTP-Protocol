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

WebBrowsers::WebBrowsers(std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request(0),indice(0),check_error(false)
{
	
	std::cout << GREEN << "Connection......\n";


	
}
WebBrowsers::~WebBrowsers()
{
	if (file_descriptor > 0)
		close(file_descriptor);
	if (request != 0)
	{
		delete request;
		request = 0;
	}

}

/*** if the server receives a request for a webpage from a client,				  **/
/*** the server will parse the request and pass it to a Response object which 	  **/
/*** will fetch the contents of the webpage and construct the HTTP response 	  **/
/*** with the HTML content in the message body and the appropriate headers,		  **/
/***  such as the Content-Type and Content-Length headers.      				 ***/



int WebBrowsers::Read_request()
{

		int recv_s;
		char buffer[BUFFUR_SIZE];
		std::string header ;
	
		value = 0;
		
		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/

		/*******This call returns the length of the incoming message or data. If a datagram packet is too long to fit in the supplied buffer, datagram sockets discard excess bytes. If data is not available for the socket socket, and socket is in blocking mode, the recv() call blocks the caller until data arrives. If data is not available and socket is in nonblocking mode, recv() returns a -1 and sets the error code to EWOULDBLOCK.*/
	
		recv_s = recv(file_descriptor, buffer,BUFFUR_SIZE, 0 );

		if(recv_s < 0)
		{
			std::cout << "No message are available to be received\n";
			value = 1;
			return 2;
		}else if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			value = 1;
			return 2;
		}
	
		if(request == NULL)
		{
			read_buffer = read_buffer + std::string(buffer, recv_s);
			if(request == NULL && recv_s <= BUFFUR_SIZE && (read_buffer.find("\r\n\r\n") != std::string::npos ))
			{
				
				// get all the request with body ou without body
				
				header = read_buffer.substr(0, read_buffer.find("\r\n\r\n"));
			
				request = new Request(header);
				if((read_buffer.substr(read_buffer.find("\r\n\r\n") + 4, read_buffer.size())).empty() == 0)
				{
				
					request->get_request_header("body") = read_buffer.substr(read_buffer.find("\r\n\r\n") + 4, read_buffer.size() - 1);
					if(request->get_request_header("body").empty() == 0)
					{
						if(request->get_content_length_exist() == 0 && request->get_transfer_encoding().find("chunked") == std::string::npos)
						{
			
							request->get_request_header("body").clear();
							value = 1;
							request->set_Status_code(400);
							return 0; 
						}
					
					
						if(request->get_transfer_encoding().find("chunked") != std::string::npos && EndChunked(request->get_request_header("body"), "0\r\n\r\n") == 1)
						{
							std::string body_chunk;
							std::string body_final;
							body_chunk.append(std::string(request->get_request_header("body")));
							std::string subchunk = body_chunk.substr(0,100);
							int			chunksize = strtol(subchunk.c_str(), NULL, 16);
			 				size_t		i = 0;
							while (chunksize)
							{
								i = body_chunk.find("\r\n", i) + 2;
								body_final += body_chunk.substr(i, chunksize);
						
								if(EndChunked(body_final, "0\r\n\r\n") == 1)
								{
									break ;
								}
								i += chunksize + 2;
								subchunk = body_chunk.substr(i, 100);
								chunksize = strtol(subchunk.c_str(), NULL, 16);
								subchunk = body_chunk.substr(0,100);
						}
						request->get_request_header("body").clear();
						request->get_request_header("body").append(std::string(body_final));
						value = 1;
					}
					}
				}
		
				
				if (request->get_type_request() == "GET" || request->get_type_request() == "DELETE")
				{
					value = 1;
				}

				if(request->get_type_request() == "POST" && request->get_request_header("body").empty() != 0)
				{

					value = 1;
				}
				if(request->get_type_request() == "POST" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
				{
					value = 1;
				}
			
				
			}
			read_buffer.clear();
		}
		else if (request != NULL)
		{
			
				if(request->get_content_length_exist() == 0 && request->get_transfer_encoding().find("chunked") == std::string::npos)
				{
			
						request->get_request_header("body").clear();
						value = 1;
						request->set_Status_code(400);
						return 0; 
				}
			
			if(request->get_transfer_encoding().find("chunked") != std::string::npos)
			{
			
				std::string body_final;
				std::cout << YELLOW << "Wait......\n";
				for(int i = 0; i < recv_s; i++)
				{
					request->get_request_header("body").push_back(buffer[i]);
				}
				//request->get_request_header("body").append(buffer, recv_s);				
				if(EndChunked(request->get_request_header("body"), "0\r\n\r\n") == 1)
				{
			 		std::string subchunk = request->get_request_header("body").substr(0,100);
					int			chunksize = strtol(subchunk.c_str(), NULL, 16);
			 		size_t		i = 0;
					while (chunksize)
					{
						i = request->get_request_header("body").find("\r\n", i) + 2;
						body_final.append(std::string(request->get_request_header("body").substr(i, chunksize)));
					
						i += chunksize + 2;					
						subchunk = request->get_request_header("body").substr(i, 100);
						chunksize = strtol(subchunk.c_str(), NULL, 16);
						std::string subchunk = request->get_request_header("body").substr(0,100);
					}
					request->get_request_header("body").clear() ;
					request->get_request_header("body").append(std::string(body_final));
				
					value = 1;
			 	 }

			}else{
					std::cout << YELLOW << "wait......\n";	

						// for(int i = 0; i < recv_s; i++)
						// {
						// 	request->get_request_header("body").push_back(buffer[i]);
						// }
						request->get_request_header("body").append(buffer, recv_s);		
					if (request->get_type_request() == "POST" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
					{
						value = 1;
					}
					if (request->get_type_request() == "GET" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
					{
						value = 1;
					}

			}	
		}
	
	return value;
}


int WebBrowsers::EndChunked(std::string &buffer, const std::string &end_check)
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
	if(request->get_Status_code() == 400 || request->get_Status_code() == 405 || request->get_Status_code() == 404 ||  request->get_Status_code() == 403 || request->get_Status_code() == 413)
	{
		check_error = true;
		path_access = request->error_pages(request->get_Status_code());
	}
	
	

}
void WebBrowsers::prepareResponse()
{
	int code_status;
	int value_status = 0;
	int delete_indice = 0;
	int error = 0;
	int count;
	std::string header;
	send_byte = 0;
	
	
	check_error_page();
	std::ifstream file_check(path_access.c_str(), std::ofstream::in);
	if(((!file_check || !file_check.is_open() || !file_check.good()) ) && Locations->get_http_redirection() == 0)
	{
		error = 1;
		request->set_Status_code(404);
		path_access = request->error_pages(request->get_Status_code());

		file_check.close();
	}
	if(autoindex == 1)
	{
		value_status = 3;
		file_check.close();
	}else if(autoindex == 0 && error == 0 && check_error == 0)
	{
		count = request->check_cgi();
		if(count > 0)
			value_status = 2;
		if(path_access.find(".php", path_access.length() - 4) != std::string::npos && value_status != 2)
		{
			request->set_Status_code(500);
			path_access = request->error_pages(request->get_Status_code());
			error = 1;
		}else if(path_access.find(".py", path_access.length() - 3) != std::string::npos && value_status != 2)
		{
			request->set_Status_code(500);
			path_access = request->error_pages(request->get_Status_code());
			error = 1;
		}
		
		
		file_check.close();
	}

	if(request->get_type_request() == "DELETE")
	{
		delete_indice = 2;
	}
	code_status = request->get_Status_code();
	std::map<unsigned int, std::string> map_Codestatus = request->Status_codes_means();
	file_file_descriptor = open(path_access.c_str(), O_RDONLY);
	response Response;
	if(error == 1 || check_error == true || (value_status == 0 && delete_indice == 0))
	{
		response_buffer = Response.response_header(0 , 0, path_access, code_status, map_Codestatus, Locations, request, header);
		indice = 2;
		delete request;
		request = 0;

	}else if(value_status == 2 && delete_indice == 0 && error == 0)
	{
		std::string body;
		
		header = request->cgi_start(body);
		if(request->get_Status_code() == 500)
		{
			path_access =  request->error_pages(request->get_Status_code());
			response_buffer = Response.response_header(0 ,0, path_access, code_status, map_Codestatus, Locations, request, header);
		}else
		{
			response_buffer = Response.response_header(body.size() ,1, path_access, code_status, map_Codestatus, Locations, request, header);
			response_buffer = response_buffer + body;
			file_file_descriptor = 0;
		}

		indice = 2;
		delete request;
		request = 0;
	}else if(value_status == 3 && delete_indice == 0)
	{
		
		std::string str;
		request->auto_index(str,  path_access);
		response_buffer = Response.response_header(str.size() ,1, path_access, code_status, map_Codestatus, Locations, request, header);
		response_buffer = response_buffer + str;
		file_file_descriptor = 0;
		indice = 2;
		delete request;
		request = 0;
	}else if(delete_indice == 2)
	{
		std::string path;
		request->delete_request(path);
		if(request->get_Status_code() == 404)	
		{
			path_access = path;
			response_buffer = Response.response_header(0 , 0, path_access, code_status, map_Codestatus, Locations, request, header);
		}else
		{
			response_buffer = Response.response_header(0 ,1, path_access, code_status, map_Codestatus, Locations, request, header);
			file_file_descriptor = 0;
		}
			
		indice = 2;
		delete request;
		request = 0;

	}
}

int WebBrowsers::send_response()
{
	if(indice == 2)
	{
		if(send1() == -1)
		{
			return -1;
		}
	}else if(indice == 3)
	{
		if(send2() == -1)
		{
			return -1;
		}
	}
	return 1;
}

int WebBrowsers::send1()
{
	
	if(send(file_descriptor, response_buffer.c_str(), response_buffer.size(), 0) == -1)
	{
		std::cout << "RED" << "Send failed\n";
		return -1;
	}
	response_buffer.clear();
	indice = 3;
	delete request;
	request = 0;
	return 1;

}

int WebBrowsers::send2()
{
	int fd;
	char 	buff[BUFFUR_SIZE];
	if(file_file_descriptor == 0)
	{
		delete request;
		value = 0;
		indice = 0;
		request = NULL;
		std::cout << GREEN << "Sending file to client.....\n";
		return 1;
	}
	fd = read(file_file_descriptor, buff, BUFFUR_SIZE);
	if(fd <= 0)
	{
		close(file_file_descriptor);
		delete request;
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request = NULL;
	}
	/****** A connection can be dropped by a peer socket and a SIGPIPE signal generated at a later time if data delivery is not complete.*/
	if(send(file_descriptor, buff, fd, 0) == -1)
	{
		std::cout << RED << "Send failed\n";
		return -1;
	}
	

	if (fd < BUFFUR_SIZE)
	{
		std::cout << GREEN << "Sendig file to client !\n";
		close(file_file_descriptor);
		delete(request);
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request = NULL;

	}
	return 1;
}



