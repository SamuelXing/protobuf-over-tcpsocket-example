// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "messages.pb.h"

#define PORT 9999 

void read(int new_socket);

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
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
	read(new_socket);
	send(new_socket, "received!", 11, 0);
	return 0; 
} 

void read(int new_socket) {
	int valread;
	char buffer_header[5] = {0}; 
	valread = read( new_socket , buffer_header, 5);
	int msg_size;
	memcpy(&msg_size, buffer_header, 4);
	std::cout << "buffer size: " << msg_size << std::endl;
	char* buffer_msg = (char*)malloc(msg_size*sizeof(char));
	memset(buffer_msg, '\0', sizeof(char)*msg_size);
	int length = 0;
	for(length = 0; msg_size != 0; length += valread) {
		valread = read( new_socket , buffer_msg+length, msg_size);
		msg_size -= valread;
	}
	std::cout << "msg length: " << length << std::endl;
	std::cout << "msg received!" << std::endl;
	Messages::Matrix message;
	if (!message.ParseFromString(std::string(buffer_msg, length)) || !message.IsInitialized()) {
		std::cout << "msg err" << std::endl;
		exit(-1);
	}
	std::cout << "rows: " << message.rows() << std::endl;
	std::cout << "cols: " << message.cols() << std::endl;
	//std::string msg_content = message.stringdata() ;
	//std::cout << "data size: " << msg_content.size() << std::endl;
	//std::cout << "msg content: " << message.stringdata(0) << std::endl;
	std::ofstream out("output.txt");
	out << message.stringdata(0);
	out.close();	
	free(buffer_msg);
}

