# Building-HTTP-Server-from-Scratch---HTTP-Protocol
42 project, recoding our own web server in C++. A program capable of running an HTTP server, handling requests, and parsing configuration files.




About This project:
-----------------------



The story is, the server keep listening any message it received, then we need to analyze what the useful information in the message by parsing it. The useful information we care about is the file name (with path) and file extension. The server then open the file according to the path and put the content of the file into a reply-message which we will later send to the client. Before sending the reply-message, we should first tell the client what kind of file content type we are going to send, maybe image file (.jpg, .png, ...) or txt file (.html, .doc, ...) 



--> Notice that the client needs to know of the existence of and the address of the server, but the server does not need to know the address of the client pripr to the connection bieng established. Notice also that once a connection is established, both sides can send and receive information.


The system calls for establishing a connection are somewhat different for the client and the server, but both involve the basic construct sockets.

A sockets is one end of an interprocess communication channel. the two processes each establish their own socket.

<img width="985" alt="Screen Shot 2023-04-01 at 3 28 08 PM" src="https://user-images.githubusercontent.com/87101785/229298449-d98f599c-12cb-45d2-a143-20df6baed1cf.png">


-----> when a socket is created, the program has to specify the address domain and socket type.

<img width="985" alt="Screen Shot 2023-04-01 at 3 33 42 PM" src="https://user-images.githubusercontent.com/87101785/229298780-3a67ab81-d97b-4ef4-924c-cb5cfcd97f92.png">

Two processes (client and server) can communicate with each other only if their sockets are of the same type and the same domain

There is two types of socket:

stream sockets and datagram sockets each uses its own communications protocol.

<img width="1124" alt="Screen Shot 2023-04-01 at 3 56 50 PM" src="https://user-images.githubusercontent.com/87101785/229301221-07c6bed9-5923-46d2-80d1-6ba7b1b2eb89.png">


