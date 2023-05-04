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


#define BUFFUR_SIZE 30000

// WebBrowsers::WebBrowsers()
// {
// 	file_descriptor = 0;
// 	//file_descriptor = 0;
// 	std::cout << "hello, thie is new client\n";
// }

WebBrowsers::WebBrowsers(std::set<server*>& servers ) : file_descriptor(0),value(0),servers(servers),request_Headers(0),indice(0)
{
	
	std::cout << "Connection......\n";


	
}
WebBrowsers::~WebBrowsers()
{
	std::cout << "Destructer client---> Client disconnected\n";
	if (file_descriptor > 0)
		close(file_descriptor);
	if (request_Headers != 0)
	{
		delete request_Headers;
		request_Headers = 0;
	}

}

int WebBrowsers::Read_request()
{

	//std::cout << "read_request\n";
		int recv_s;
		char buffer[BUFFUR_SIZE];
		std::string read_buffer;
		value = 0;

		//For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much data as is currently available—up to the size of the buffer specified
				
		/****recv() returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

		Wait! recv() can return 0. This can mean only one thing: the remote side has closed the connection on you! A return value of 0 is recv()’s way of letting you know this has occurred.*/

		/*******This call returns the length of the incoming message or data. If a datagram packet is too long to fit in the supplied buffer, datagram sockets discard excess bytes. If data is not available for the socket socket, and socket is in blocking mode, the recv() call blocks the caller until data arrives. If data is not available and socket is in nonblocking mode, recv() returns a -1 and sets the error code to EWOULDBLOCK.*/

		recv_s = recv(file_descriptor, buffer,BUFFUR_SIZE, 0 ); 
				//std::cout << buffer << endl;

		if(recv_s < 0)
		{
			std::cout << "No message are available to be received\n";
			return 2;
		}else if(recv_s == 0)
		{
			std::cout << "Client disconnected\n";
			return 2;
		}
		if(request_Headers == NULL)
		{
			read_buffer = read_buffer + buffer;
		}else if(request_Headers != NULL)
		{
			std::cout << "request it is not empty\n";
		}
		std::cout << "read_buffer:\n";
		std::cout << read_buffer << endl;
	
// If the datagram or message is not larger than the buffer specified,
// check if all the informations of our request exist in buffer
		if(recv_s < BUFFUR_SIZE)
		{		
			// send request
			if(request_Headers == NULL)
			{
				request_Headers = new Request(read_buffer);
			}
			read_buffer.clear();
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
	
	request_Headers->check_request_with_config_file(servers);

}

void WebBrowsers::ThePath_of_acces_file()
{
	path_access = request_Headers->path_of_file();
}
void WebBrowsers::prepareResponse()
{
	int status;
	int code_status;
	int value = 0;
	int count;
	send_byte = 0;
	//unsigned int length = atoi(request_Headers->get_request_header("Content-Length").c_str());
	//request_Headers->check_client_max_body_size(length);
	
	// check if this path exist
	std::cout << "path_access->" << path_access << endl;
	ifstream file_check(path_access.c_str(), ofstream::in);
	if(!file_check || !file_check.is_open() || !file_check.good())
	{
		std::cout << "file not found\n";
		request_Headers->set_Status_code(404);
		// close(file_check);
	}else
	{
		std::cout << "file exist\n";
		count = request_Headers->check_cgi();
		if(count > 0)
			value = 2;
		// close(file_check);
	}
	status = request_Headers->get_indice();
	code_status = request_Headers->get_Status_code();
	map<unsigned int, string> map_Codestatus = request_Headers->Status_codes_means();
	file_file_descriptor = open(path_access.c_str(), O_RDONLY);
	response Response;
	if(status == 0 && value == 0)
	{
		response_buffer = Response.response_header(0 , 0, path_access, code_status, map_Codestatus);
		// int size_actuel = BUFFUR_SIZE;
		// if (send_byte + size_actuel > response_buffer.size())
		// 	size_actuel= response_buffer.size() - send_byte;
		// send(file_descriptor, response_buffer.c_str() + send_byte,size_actuel, 0);
		// send_byte = send_byte + size_actuel;
		// if (send_byte == response_buffer.size())
		// {
		// 	std::cout << "size and response_buffer-->" << send_byte << endl;
		// 	response_buffer.clear();
			indice = 2;
			delete request_Headers;
			request_Headers = 0;

		// }
	}else if(status == 0 && value != 0)
	{
		request_Headers->cgi_start();
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
	std::cout << "send1 open\n";

	send(file_descriptor, response_buffer.c_str() + send_byte,response_buffer.size(), 0);
	// std::cout << "size and response_buffer-->" << send_byte << endl;
	response_buffer.clear();
	indice = 3;
	delete request_Headers;
	request_Headers = 0;

}

void WebBrowsers::send2()
{
	int fd;
	//char hello[100] = "hello souchen";
	char 	buff[BUFFUR_SIZE];
	if(file_file_descriptor == 0)
	{
		delete request_Headers;
		value = 0;
		indice = 0;
		request_Headers = NULL;
		return ;
		std::cout << "error1\n";
	}
	fd = read(file_file_descriptor, buff, BUFFUR_SIZE);
	
	// std::cout << "fd = " << fd << endl;
	if(fd <= 0)
	{
		close(file_file_descriptor);
		delete request_Headers;
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request_Headers = NULL;

		std::cout << "error read faild \n";
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
		delete(request_Headers);
		indice = 0;
		value = 0;
		file_file_descriptor = 0;
		request_Headers = NULL;
	}
}



