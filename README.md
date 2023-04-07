# Building-HTTP-Server-from-Scratch---HTTP-Protocol
42 project, recoding our own web server in C++. A program capable of running an HTTP server, handling requests, and parsing configuration files.



Creating a web server in C++ is a great way to learn the language and gain experience in web development. It is a relatively simple process that requires a few basic steps. First, you will need to create a socket to listen for incoming connections. Then, you will need to bind the socket to a port and start listening for incoming requests. Finally, you will need to write the code to handle the requests and send back the appropriate response. With these steps, you can create a basic web server in C++.







--->Create a Socket :
---------------------

The first step in creating a web server in C++ is to create a socket. A socket is a communication endpoint that allows two programs to communicate with each other. In this case, the socket will be used to listen for incoming requests from web browsers. To create a socket, you will need to use the socket() function from the C++ standard library. This function takes three parameters: the address family, the type of socket, and the protocol. The address family should be set to AF_INET, the type should be set to SOCK_STREAM, and the protocol should be set to 0. Once the socket is created, it can be used to listen for incoming requests.

-->Bind the Socket to a Port:
-------------------------

The next step is to bind the socket to a port. A port is a number that is used to identify a particular application or service. When a web browser sends a request, it will specify the port number that it is trying to connect to. By binding the socket to a port, you are telling the operating system that this socket should be used to listen for incoming requests on that port. To bind the socket to a port, you will need to use the bind() function from the C++ standard library. This function takes three parameters: the socket, the address of the socket, and the size of the address. The address should be set to the port number that you want to bind the socket to.

-->Start Listening for Requests:
-------------------------------


Once the socket is bound to a port, you can start listening for incoming requests. To do this, you will need to use the listen() function from the C++ standard library. This function takes two parameters: the socket and the backlog. The backlog is the maximum number of connections that can be waiting to be accepted. Once the listen() function is called, the socket will start listening for incoming requests.

Handle Requests and Send Responses
The final step is to write the code to handle the requests and send back the appropriate response. This is the most important part of creating a web server in C++. You will need to write code to parse the request, determine what the request is asking for, and then send back the appropriate response. This can be done using the read() and write() functions from the C++ standard library. The read() function will read the request from the socket and the write() function will write the response back to the socket.






Our project steps:
-------------------

In summary, our server will have a socket that:

listens for incoming network connections and puts them on a Queue
accepts a network connection from the Queue one at a time
reads the data (Request) sent from the client over the network connection
sends data (Response) to the client over the network connection.




<img width="762" alt="Screen Shot 2023-04-07 at 2 05 35 PM" src="https://user-images.githubusercontent.com/87101785/230622271-b71a7b1a-5a0f-4a9c-bc46-e69930b8c973.png">



