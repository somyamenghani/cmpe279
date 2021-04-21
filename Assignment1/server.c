// Server side C/C++ program to demonstrate Socket programming

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pwd.h>
#define PORT 80
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[102] = {0};
    char *hello = "Hello from server";
    pid_t child,parent;
    struct passwd* passwd_p;
    int status;

    printf("execve=0x%p\n", execve);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to port 80
    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    //                                               &opt, sizeof(opt)))
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 80
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //Separating logic and Forking 
child=fork();
if(child==0)
{
      passwd_p = getpwnam("nobody");
             printf("Child Process: UID of nobody=%ld\n",(long) passwd_p->pw_uid);
        if (setuid(passwd_p->pw_uid) != 0)   
            perror("Child Process: setuid() error");
        else
            printf("Child Process: UID after setuid() = %ld\n",(long) getuid());
       valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
}
   else if (child > 0){
        //Waiting for child process to complete
        printf("Parent Process: Waiting for child process to complete\n");
        if((parent = wait(&status)) < 0){
            perror("Parent Process: Error in wait");
            _exit(1);
        }
        printf("Parent Process: Forked child pid: %d\n", child); 
        printf("Log: Parent Process: Current pid = %d\n",getpid());
    }
    else{
        perror("Error occurred fork() failed");
        _exit(2);                                                                                                                                          
    }
   
    return 0;
}
