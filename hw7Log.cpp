#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#define PORT 8365 


using namespace std;

int main(){
    //https://www.geeksforgeeks.org/socket-programming-cc/
    int serverfd;
    int new_socket;
    int valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlength = sizeof(address);
    char buffer[1024] = {0};
    char *message = "Logger sees you!";

    // create socket
    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        cout << "Socket failed" << endl;
        exit(0);
    }


    // Attach socket to port 8365
    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        cout << "Set socket opt" << endl;
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if(bind(serverfd, (struct sockaddr *)&address, sizeof(address)) < 0){
        cout << "Bind failed" << endl;
        exit(0);
    }

    if(listen(serverfd, 3) < 0){
        cout << "Listening" << endl;
        exit(0);
    }

    if((new_socket = accept(serverfd, (struct sockaddr *)&address, (socklen_t*)&addrlength)) < 0){
        cout << "Accept" << endl;
        exit(0);
    }

    valread = read( new_socket, buffer, 1024);
    cout << string(buffer) << endl;

    send( new_socket, message, sizeof(message), 0);
    cout << "Message sent" << endl;

    return 0;
}