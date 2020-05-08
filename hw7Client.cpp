#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#define PORT 8365 


using namespace std;

int main(){
    int sock = 0;
    int valread;
    struct sockaddr_in serv_addr;
    char *message = "Client sees you!";
    char buffer[1024] = {0};
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) > 0){
        cout << "Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "einstein.etsu.edu", &serv_addr.sin_addr) <= 0){
        cout << "Invalid address / Address not supported" << endl;
        return -1;
    }


    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "Connection failed" << endl;
        return -1;
    }


    send(sock, message, sizeof(message), 0);
    cout << "Client message sent" << endl;

    valread = read(sock,buffer,1024);
    cout << string(buffer) << endl;


    return 0;
}