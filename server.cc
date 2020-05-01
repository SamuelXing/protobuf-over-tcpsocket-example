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
#include <utility>
#include <fstream>

#include "messages.pb.h"

#define PORT 9999 

using namespace std;

// This function reads protobuf msg from socket to a string
void read(int new_socket, string& msg);

// Iterates though all people in the AddressBook and prints info about them.
void list_people(const Messages::AddressBook& address_book);

// main
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
	cout << "server start listening on "<< PORT <<"...\n";
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	while ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))) 
	{ 
		if(new_socket < 0) {
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} else
		{
			string message;
			read(new_socket, message);
			Messages::AddressBook address_book;
			if (!address_book.ParseFromString(message)) {
				cerr << "Failed to parse address book." << endl;
				return -1;
			}
			list_people(address_book);
		}
	} 

	return 0; 
} 

void read(int new_socket, string& msg) {
	int valread;
	char buffer_header[sizeof(size_t)] = {0}; 
	valread = read( new_socket , buffer_header, sizeof(size_t));

	size_t msg_size;
	memcpy(&msg_size, buffer_header, sizeof(size_t));

	char* buffer_msg = (char*)malloc(msg_size*sizeof(char));
	memset(buffer_msg, '\0', sizeof(char)*msg_size);
	int length = 0;
	for(length = 0; msg_size != 0; length += valread) {
		valread = read( new_socket , buffer_msg+length, msg_size);
		msg_size -= valread;
	}

	msg = std::string(buffer_msg, length);
	free(buffer_msg);
}

void list_people(const Messages::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const Messages::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.email() != "") {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const Messages::Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case Messages::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case Messages::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case Messages::Person::WORK:
          cout << "  Work phone #: ";
          break;
        default:
          cout << "  Unknown phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
    
  }
}
