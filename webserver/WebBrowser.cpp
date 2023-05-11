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

// WebBrowsers::WebBrowsers()
// {
// 	file_descriptor = 0;
// 	//file_descriptor = 0;
// 	std::cout << "hello, thie is new client\n";
// }

WebBrowsers::WebBrowsers(std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request(0),indice(0)
{
	
	std::cout << "Connection......\n";


	
}
WebBrowsers::~WebBrowsers()
{
	std::cout << "Destructer client---> Client disconnected\n";
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

	//std::cout << "read_request\n";
		int recv_s;
		char buffer[BUFFUR_SIZE];
		//std::string read_buffer;
		value = 0;
		
		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/

		/*******This call returns the length of the incoming message or data. If a datagram packet is too long to fit in the supplied buffer, datagram sockets discard excess bytes. If data is not available for the socket socket, and socket is in blocking mode, the recv() call blocks the caller until data arrives. If data is not available and socket is in nonblocking mode, recv() returns a -1 and sets the error code to EWOULDBLOCK.*/

		recv_s = recv(file_descriptor, buffer,BUFFUR_SIZE, 0 ); 
		// std::cout << "buffer -->" << buffer << endl;
		//std::cout << buffer << endl;
		// std::cout << "octet-->" << recv_s << endl; 
		if(recv_s < 0)
		{
			std::cout << "No message are available to be received\n";
			// value = 1;
			return 2;
		}else if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			// value = 1;
			return 2;
		}
		if(request == NULL)
			read_buffer = read_buffer + string(buffer, recv_s);
			std::cout << "Buffer :" << read_buffer << endl; 
			if(request == NULL && recv_s <= BUFFUR_SIZE && read_buffer.find("\r\n\r\n") != std::string::npos)
			{
				request = new Request(read_buffer);

				read_buffer.clear();
				if (request->get_type_request() == "GET" || request->get_type_request() == "DELETE")
					value = 1;
				else if (request->get_type_request() == "POST" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
					value = 1;
			}
			else if (request != NULL)
			{
				for(int i = 0; i < recv_s; i++)
					request->get_request_header("body").push_back(buffer[i]);
				if (request->get_type_request() == "GET" || request->get_type_request() == "DELETE")
					value = 1;
				else if (request->get_type_request() == "POST" &&  request->get_request_header("Content-Length") != "" && (std::stol(request->get_request_header("Content-Length")) ==  (long)request->get_request_header("body").size()))
					value = 1;
			}
			
	return value;
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
	// if (request_headers["body"].size() >= std::stol(request_headers["Content_Lengh"]))
	// {
	// 	std::cout << "true\n";
	// 	exit(1);
	// }
	request->check_request_with_config_file(servers);

}

void WebBrowsers::ThePath_of_acces_file()
{
	path_access = request->path_of_file();
}
void WebBrowsers::prepareResponse()
{
	int status;
	int code_status;
	int value = 0;
	int count;
	send_byte = 0;
	//unsigned int length = atoi(request->get_request_header("Content-Length").c_str());
	//request->check_client_max_body_size(length);
	
	// check if this path exist
	// std::cout << "path_access->" << path_access << endl;
	//std::cout << "body final request-->" << request->get_request_header("body") << endl;
	ifstream file_check(path_access.c_str(), ofstream::in);
	if(!file_check || !file_check.is_open() || !file_check.good())
	{
		std::cout << "file not found\n";
		request->set_Status_code(404);
		file_check.close();
	}else
	{
		std::cout << "file exist\n";
		 count= request->check_cgi();
		if(count > 0)
			value = 2;
		file_check.close();
	}
	status = request->get_indice();
	code_status = request->get_Status_code();
	map<unsigned int, string> map_Codestatus = request->Status_codes_means();
	file_file_descriptor = open(path_access.c_str(), O_RDONLY);
	// std::cout << "file_file-->" << file_file_descriptor << endl;
	response Response;
	if(status == 0 && value == 0)
	{
		response_buffer = Response.response_header(0 , 0, path_access, code_status, map_Codestatus);
		indice = 2;
		delete request;
		request = 0;

	}else if(status == 0 && value != 0)
	{
		std::string body;
		request->cgi_start(body);
		response_buffer = Response.response_header(body.size() ,1, path_access, code_status, map_Codestatus);
		response_buffer = response_buffer + body;
		// std::cout << "response-->" << response_buffer << endl;
		file_file_descriptor = 0;
		indice = 2;
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
	//char hello[100] = "hello souchen";
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
	// std::string str = "HTTP/1.1 200 OK\r\nContent-Length: 363\r\n\r\n";
	// send(file_descriptor, str.c_str(), str.length(), 0);
	//std::cout << "befaure\n";
	
	//std::cout << "buffer->" << buff << endl;
	send(file_descriptor, buff, fd, 0);
	
	
	//write(file_descriptor, hello, strlen(hello));
	//std::cout << "after\n";
	if (fd < BUFFUR_SIZE)
	{
		// if all the size of the image or the text is sended
		std::cout << "sendig file to client !\n";
		close(file_file_descriptor);
		delete(request);
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request = NULL;
	}
}



