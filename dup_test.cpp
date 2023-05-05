// CPP program to illustrate dup2() 
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>


// dup2()

int main()
{
    int file_desc = open("tricky.txt",O_WRONLY | O_APPEND);
      
    // here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1); 
          
    // All the printf statements will be written in the file
    // "tricky.txt"
    printf("I will be printed in the file tricky.txt\n");
      
return 0;
}

// pipe()


/****int pipe(int fds[2]);                                                                                         

Parameters :
fd[0] will be the fd(file descriptor) for the 
read end of pipe.
fd[1] will be the fd for the write end of pipe.*/


//Conceptually, a pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process. In UNIX Operating System, Pipes are useful for communication between related processes(inter-process communication).

/*Pipe is one-way communication only i.e 
we can use a pipe such that One process write to the pipe, and the other process reads from the pipe. It opens a pipe,
 which is an area of main memory that is treated as a “virtual file”.*/


 /***The pipe can be used by the creating process, as well as all its child processes, for reading and writing. One process can write to this “virtual file” or pipe and another related process can read from it.**/


 /*****execve() executes the program referred to by pathname.  This
       causes the program that is currently being run by the calling
       process to be replaced with a new program, with newly initialized
       stack, heap, and (initialized and uninitialized) data segments.*/



       /*****What is CGI?
CGI stands for Common Gateway Interface, it enables web-server to provide dynamic web-page to clients. When client sends request(usually GET, POST method) to server, web-server makes a process to run the requested data. Then send the result back to client.


CGI Workflow
How to Programming CGI?
[Step1] Make process by using fork( ). Also open pipes.

[Step 2] Execute CGI in child process.

fd = open(//temporary file to record cgi result);
pipe(tubes);
if ((cgi_pid = fork())== 0) // child process
{
  close(tubes[1]);  
  dup2(tubes[0], 0);   
  execve(args[0], args, env);
}
args[0] has to be a path of cgi program or cgi script. Such as “/usr/local/bin/php-cgi”
args[1] has to be a path of cgi file . If it script it has to be NULL.
args[2] == NULL
env has parsed request and some more variables according to RFC3875
Meta-variables with names beginning with "HTTP_" contain values read    from the client request header fields, if the protocol used is HTTP.    The HTTP header field name is converted to upper case, has all    occurrences of "-" replaced with "_" and has "HTTP_" prepended to    give the meta-variable name.


[STEP 3] Pass requested data through pipe in Parent Process.

CGI will give result to web-server and web-server will make response based on this result.*/