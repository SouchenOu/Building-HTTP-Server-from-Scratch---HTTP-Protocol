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
#include "../headers/server.hpp"
#include "../headers/WebBrowser.hpp"
#include <fcntl.h>
# define white_espace "; \t"


Webserver::Webserver()
{
	std::cout << GREEN << "Welcome this is my server\n";
}

Webserver::~Webserver()
{}

void	Webserver::push_in_server(server *serv)
{
	servers.insert(serv);
}


void Webserver::parcing_config_file(std::string config_file)
{

	size_t cmp = 0;
//int size;
//Ifstream c++ is a file input stream that allows us to read any information contained in the file

    std::ifstream read_file(config_file.c_str());
	if(is_empty(read_file))
	{
		std::cout << RED << "Config_file is empty\n";
		exit(0);
	}
	
// now we should convert ifstream to string
	std::string the_str (std::istreambuf_iterator<char>(read_file),(std::istreambuf_iterator<char>()));
	read_file.close();
	std::vector<std::string> config_line = ft_divise(the_str, "\n");
	
	while (cmp < config_line.size())
	{
		std::vector<std::string>::iterator iter1 = config_line.begin() + cmp;
		std::vector<std::string> world_line = ft_divise(*iter1, " ");
		
		std::vector<std::string>::iterator iter2 = world_line.begin();
		if (*iter2 == "server")
		{
			server *serv = parse_server(config_line, &cmp);
			for(std::set<server*>::const_iterator iter1 = servers.begin(); iter1 != servers.end() ; iter1++)
			{
				if((*iter1)->get_ip_address() == serv->get_ip_address() && (*iter1)->get_port_listen() == serv->get_port_listen())
				{
					std::set<std::string> server_names = (*iter1)->get_server_name();
					if(server_names.size() == 0 && serv->get_server_name().size() == 0)
					{
						std::cout << BLUE << "MyServer: [warn] conflicting port on" << serv->get_ip_address() << ":" << serv->get_port_listen() << ", ignored" << std::endl;
						exit(0);
					}
					for(std::set<std::string>::iterator iter2 = server_names.begin(); iter2 != server_names.end(); iter2++)
					{
						std::set<std::string> new_server_names = serv->get_server_name();
						for(std::set<std::string>::const_iterator iter3 = new_server_names.begin(); iter3 != new_server_names.end(); iter3++)
						{
							if((*iter2) == (*iter3))
							{
								std::cout << BLUE << "MyServer: [warn] conflicting server name on" << serv->get_ip_address() << ":" << serv->get_port_listen() << ", ignored" << std::endl;
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
	
	fd_max = 0;
	int fd_client;
//Clear an fd_set
//This macro initializes the file descriptor set set to be the empty set.
	FD_ZERO(&readfds); 
	FD_ZERO(&writefds);
	for (std::set<server*>::iterator iter = servers.begin(); iter != servers.end(); iter++)
	{
		bool add_already_use = false;
		for (std::set<server*>::iterator check = servers.begin(); check != iter; check++)
		{
			if ((*check)->get_ip_address() == (*iter)->get_ip_address() && (*check)->get_port_listen() == (*iter)->get_port_listen())

				add_already_use = true;
		}
		if (add_already_use == true)
		{
			continue;
		}
		fd_socket = (*iter)->Create_server_socket();	
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
		for(std::list<WebBrowsers*>::iterator iter1= Browsers.begin(); iter1 != Browsers.end(); iter1++)
		{
			fd_client	= (*iter1)->get_file_descriptor();
			if(fd_client == -1)
			{
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
		
		
		
		/* when select returns we know that one of our file descriptors has works for us, but select us a bit srange as i mentioned before (it is destructive)
			meaning that it changes our FD_SET, so we passed in the set of file descriptors  to tell select which file descriptors to keep an eye on and when 
			it returns now that same FD_SET containes just the file descriptors that are ready for reading, that is why we made a copy .
			we didnt want to lose the list of descriptors that i'm watching */

		//time is forever because timeout is specified as a null pointer
		/****The three middle arguments, readset, writeset, and exceptset, specify the descriptors that we want the kernel to test for reading, writing, and exception conditions****/
		activity = select(fd_max + 1, &r_fds, &w_fds, NULL, 0);

		//The select function returns the number of sockets meeting the conditions
		if((activity < 0) && (errno != EINTR))
		{
			std::cout << RED << "Select error\n";
		}
		/**********************************************************/
      	/* One or more descriptors are readable.  Need to         */
      	/* determine which ones they are.                         */
      	/**********************************************************/
		for (std::set<server*>::iterator iter2 = servers.begin(); iter2 != servers.end(); iter2++)
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
				// i enter here if client send request
				int client_socket = 0;
			 	WebBrowsers *browser = new WebBrowsers(servers);
				std::cout << GREEN << "Confirmation, accepting to receive a call from a sender\n";
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

		for(std::list<WebBrowsers*>::iterator iter3 = Browsers.begin(); iter3 != Browsers.end(); iter3++ )
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
					(*iter3)->check_request();
					(*iter3)->ThePath_of_acces_file();
					(*iter3)->prepareResponse();
				}
				else if((*iter3)->get_indice() > 0)
				{
					if((*iter3)->send_response() == -1)
					{
						FD_CLR((*iter3)->get_file_descriptor(), &readfds);
						FD_CLR((*iter3)->get_file_descriptor(), &writefds);
						close((*iter3)->get_file_descriptor());
						(*iter3)->set_file_descriptor(-1);
						delete(*iter3);
						iter3 = Browsers.erase(iter3);
					}
					
						
				}
				
			}
			
		
		

		}
	}
}



int Webserver::get_value()
{
	return value;
}

