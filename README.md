# cmpe279

# Commented and slightly modified this statement in server.c
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
 - Changed to
 - if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
 
 # Team assignment
 - Somya Menghani(Student Id:014172197)
 - Prashanth Narasimha
 
 - Assignment 1
 - For server sudo ./server
 - For client ./client
