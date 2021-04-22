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
    struct passwd* passwd_p;
    int status;

        if(argc!=2){
        perror("All arguments are not passed\n ");
        _exit(2);
    }
    
    passwd_p = getpwnam("nobody");
    printf("child.c UID of nobody=%ld\n",(long) passwd_p->pw_uid);
    if (setuid(passwd_p->pw_uid) != 0) {
        perror("Error in setuid\n");
        _exit(2);
    }
    else
        printf("UID after setuid() = %ld\n",(long) getuid());
    valread = read((int)*argv[1], buffer, 1024);
    printf("%s\n",buffer ); 
    send((int)*argv[1], hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n");
    return 0;
}