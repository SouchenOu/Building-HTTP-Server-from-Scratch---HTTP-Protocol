/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserver.hpp"
//#include "parce_config_file.cpp"
#include "../headers/server.hpp"
#include "../headers/WebBrowser.hpp"
#include <fcntl.h>
// #include "../headers/Request.hpp"
# define white_espace "; \t"


Webserver::Webserver()
{
	std::cout << "Welcome this is my server\n";
}

Webserver::~Webserver()
{
	
}

void	Webserver::push_in_server(server *serv)
{
	servers.insert(serv);
}


void Webserver::parcing_config_file(string config_file)
{

	size_t cmp = 0;
	//int size;
	//Ifstream c++ is a file input stream that allows us to read any information contained in the file

    std::ifstream read_file(config_file.c_str());
	// firstly we need to change the get position value to know the size of our file
	// here it will stop in the end of our file (to calcule the number exact of our character in the file)
	// read_file.seekg(0, ios::end);
	// size = read_file.tellg();
	// if(size == 0)
	// {
	// 	std::cout << "Error: File is empty\n";
	// }
	//string str;
	// if(!getline(read_file, str))
	// {
	// 	cout << "config file is empty\n";
	// }
	// now we should convert ifstream to string
	string the_str (istreambuf_iterator<char>(read_file),(istreambuf_iterator<char>()));
	read_file.close();
	vector<string> config_line = ft_divise(the_str, "\n");
	// vector<string>::iterator ii ;
	// for(ii = config_line.begin(); ii != config_line.end(); ii++)
	// {
	// 	std::cout << "Line by line -->" << *ii << std::endl; 
	// }
	// exit(0);
	while (cmp < config_line.size())
	{
		vector<string>::iterator iter1 = config_line.begin() + cmp;
		vector<string> world_line = ft_divise(*iter1, " ");
		// std::cout << "word[0] -->" << world_line[0] << endl;
		// std::cout << "word[1] -->" << world_line[1] << endl;

		// vector<string>::iterator ip ;
		// for(ip = word_line.begin(); ip != word_line.end(); ip++)
		// {
		// 	std::cout << "elem->" << *ip << endl;
		// }
		vector<string>::iterator iter2 = world_line.begin();
		if (*iter2 == "server")
		{
			server *serv = parse_server(config_line, &cmp);
			// std::cout << "port:" << serv->get_port_listen() << endl;
			// std::cout << "ip:" << serv->get_ip_address() << endl;
			for(set<server*>::iterator iter1 = servers.begin(); iter1 != servers.end() ; iter1++)
			{
				if((*iter1)->get_ip_address() == serv->get_ip_address() && (*iter1)->get_port_listen() == serv->get_port_listen())
				{
					set<string> server_names = (*iter1)->get_server_name();
					for(set<string>::iterator iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
					{
						for(set<string>::iterator iter3 = serv->get_server_name().begin(); iter3 != serv->get_server_name().end(); iter3++)
						{
							if((*iter2) == (*iter3))
							{
								std::cout << BLUE << "MyServer: [warn] conflicting server name on" << serv->get_ip_address() << ":" << serv->get_port_listen() << ", ignored" << endl;
								exit(0);
							}
						}
					}
				}
			}
			push_in_server(serv);
		}
		cmp++;
	}

}


void Webserver::Establish_connection(void)
{
	
	int fd_socket;
	//int cmp = 0;

	//int new_socket;
	// string message = "hello souchen";
	fd_max = 0;
	int fd_client;
	//Clear an fd_set
	//This macro initializes the file descriptor set set to be the empty set.
	FD_ZERO(&readfds); 
	FD_ZERO(&writefds);
	for (set<server*>::iterator server = servers.begin(); server != servers.end(); server++)
	{
		std::cout << "create socket servers\n";
		fd_socket = (*server)->Create_server_socket();	
//Add a file_descriptor to an fd_set
/*****The fd_set structure is used by various Windows Sockets functions and service providers, such as the select function, to place sockets into a "set" for various purposes, such as testing a given socket for readability using the readfds parameter of the select function.*/

/****FD_SET() adds the file descriptor "fd_socket" to the fd_set,
so that select() will return if a connection comes in
on that socket (which means you have to do accept(), etc. */
		FD_SET(fd_socket, &readfds);
		if(fd_socket > fd_max)
		{
			fd_max = fd_socket;
		}
	}


/*************************************************************/
/* Loop waiting for incoming connects or for incoming data   */
/* on any of the connected sockets.                          */
/*************************************************************/

	while(true)
	{
		r_fds = readfds;
		w_fds = writefds;
		activity = 0;

		// check if accept() failed or if client disconnected
		for(list<WebBrowsers*>::iterator iter1= Browsers.begin(); iter1 != Browsers.end(); iter1++)
		{
			fd_client	= (*iter1)->get_file_descriptor();
			if(fd_client == -1)
			{
				std::cout << "accept() failed \n";
				// close client_file_descriptor if client disconnected

				delete(*iter1);
				iter1 = Browsers.erase(iter1);
				(*iter1) = 0;
	
			}	
			
			
		}


//What if you’re blocking on an accept() call? How are you going to recv() data at the same time? “Use non-blocking sockets!” No way! You don’t want to be a CPU hog. What, then?
/*****select() gives you the power to monitor several sockets at the same time. It’ll tell you which ones are ready for reading, which are ready for writing, and which sockets have raised exceptions, if you really want to know that.*/

// wait for an activity on one of the sockets
// so wait indefinitely


/******If your application allocates sockets 3, 4, 5, 6, and 7, and you want to check all of your allocations, nfds should be set to 8, the highest socket descriptor you specified, plus 1. If your application checks sockets 3 and 4, nfds should be set to 5.*/


//Socket numbers are assigned starting with number 3 because numbers 0, 1, and 2 are used by the C socket interface.

/*****readfds
Points to a bit set of descriptors to check for reading.
******writefds
Points to a bit set of descriptors to check for writing.*/

// here in fd_max we specified file descripters that we will check if its ready for reading or ready for writing 


//The fd_max argument specifies the range of file descriptors to be tested. The select() function tests file descriptors in the range of 0 to nfds-1.


// without multeplexing , server process can entertain only one client at a time, and can not entertain other client is requests until it finishes with the current client

// with multiplexing , server can entertain multiple connected clients simultaneously

// select() works by blocking until something happens on a file descriptor.
//--> Data coming in or being able to write to a file descriptor
		
		
		/*****A server socket is considered ready for reading if there is a pending connection which can be accepted with accept; see Accepting Connections. A client socket is ready for writing when its connection is fully established;*/
		// select is constructive (select change r_fds )

		/* when select returns we know that one of our file descriptors has works for us, but select us a bit srange as i mentioned before (it is destructive)
			meaning that it changes our FD_SET, so we passed in the set of file descriptors  to tell select which file descriptors to keep an eye on and when 
			it returns now that same FD_SET containes just the file descriptors that are ready for reading, that is why we made a copy .
			we didnt want to lose the list of descriptors that i'm watching */
		activity = select(fd_max + 1, &r_fds, &w_fds, NULL, 0);

		//The select function returns the number of sockets meeting the conditions
		if((activity < 0) && (errno != EINTR))
		{
			std::cout << "select error\n";
		}
		// i enter here selon how much i click the 

		/**********************************************************/
      	/* One or more descriptors are readable.  Need to         */
      	/* determine which ones they are.                         */
      	/**********************************************************/
		for (set<server*>::iterator iter2 = servers.begin(); iter2 != servers.end(); iter2++)
		{
			/*******************************************************/
         	/* Check to see if this descriptor is ready            */
         	/*******************************************************/
			/*******************************************************/
            /* A descriptor was found that was readable 			*/
			/*  This is being done   								*/
            /* we can stop looking at the working set   			*/
            /* once we have found all of the descriptors that   	*/
            /* were ready.                                      	*/
            /********************************************************/

			// so we use fD_ISSET to check to see if that one is set, and if it is then we accept() the connection to read the request
			if (FD_ISSET((*iter2)->get_fd_socket(), &r_fds))
			{
				std::cout << "enter server -->" << (*iter2)->get_port_listen()<< endl;
				// i enter here if client send request
				int client_socket = 0;
			 	WebBrowsers *browser = new WebBrowsers(servers);
				std::cout << "Confirmation, accepting to receive a call from a sender\n";
			 	int addrlen = sizeof(browser->get_address_client());
				// //The accept() call is used by a server to accept a connection request from a client

				/*************************************************/
                /* Accept all incoming connections that are      */
                /* queued up on the listening socket before we   */
                /* loop back and call select again.              */
                /*************************************************/
			 	client_socket = accept((*iter2)->get_fd_socket(),browser->get_address_client(),(socklen_t*)&addrlen);

				browser->set_file_descriptor(client_socket);
				Browsers.push_back(browser);
				FD_SET(browser->get_file_descriptor(), &readfds);
				FD_SET(browser->get_file_descriptor(), &writefds);

			}
		
		}

		for(list<WebBrowsers*>::iterator iter3 = Browsers.begin(); iter3 != Browsers.end(); iter3++ )
		{
			if((*iter3)->get_file_descriptor() > fd_max)
			{
				fd_max = (*iter3)->get_file_descriptor();
			}
			// i will enter here untel select() doenst change r_fds to fd_socket server that clent sent to it a request 
			// other case is when the socket that is ready to read from is one of those client--> here we need to read its data and handle the connection 
			if(FD_ISSET((*iter3)->get_file_descriptor(), &r_fds))
			{
				// read incoming message....
				std::cout << BLUE << "Read incoming message" << endl;
				
				if((*iter3)->Read_request() == 2)
				{
					FD_CLR((*iter3)->get_file_descriptor(), &readfds);
					FD_CLR((*iter3)->get_file_descriptor(), &writefds);
					close((*iter3)->get_file_descriptor());
					(*iter3)->set_file_descriptor(-1);
					
					delete(*iter3);
					iter3 = Browsers.erase(iter3);
					
				}
			}
			else if((*iter3)->get_value() == 1)
			{
				if((*iter3)->get_indice() == 0)
				{
					std::cout << "prepare response\n";
					(*iter3)->check_request();
					(*iter3)->ThePath_of_acces_file();
					(*iter3)->prepareResponse();
				}
				else if((*iter3)->get_indice() > 0)
				{
					// std::cout << "send_response\n";
					(*iter3)->send_response();
				}
				
			}
			
		
			// cmp++;

			// if(cmp == 10000)
			// 	exit(1);

		}

	//handle multiple socket connections with fd_set and select 
	//When writing server programs using sockets , it becomes necessary to handle multiple connections at a time , since a server needs to serve multiple clients.

	}
}


// struct sockaddr* Webserver::get_address(void)
// {
// 	return (struct sockaddr*)(&address);
// }


int Webserver::get_value()
{
	return value;
}

