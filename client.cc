// Client side C/C++ program to demonstrate Socket programming 

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <fstream>
#include <chrono>
#include <ctime>

#include "messages.pb.h"

#define PORT 9999 

using namespace std;

// This function sends a char buffer to server
void send(int sock, string msg);

// This function will fill in a Person.
void generate_a_record(Messages::Person* person); 

// main 
int main(int argc, char const *argv[]) 
{ 
	// Verify that the version of the library that we linked against is
  	// compatible with the version of the headers we compiled against.
  	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	int sock = 0; 
	struct sockaddr_in serv_addr; 

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

	Messages::AddressBook address_book;
	// Add an address.
  	generate_a_record(address_book.add_people());
	// Write the new address book to string.
	std::string address_book_str;
	{
		if (!address_book.SerializeToString(&address_book_str)) {
		cerr << "Failed to serialize address book." << endl;
		return -1;
		}
  	}
	send(sock, address_book_str);

	return 0; 
} 

void send(int sock, string msg) {
	size_t msg_size = msg.length();
	char header[sizeof(size_t)];
	memset(header, '\0', sizeof(size_t));
	memcpy(header, (char*) &msg_size, sizeof(size_t));
	send(sock, header, sizeof(size_t), 0);
	send(sock, msg.c_str(), msg_size, 0 );
	cout << "msg sent to server...\n";
}

void generate_a_record(Messages::Person* person) {
  int id = 0;
  person->set_id(id);
  string name = "John Doe";
  person->set_name(name);
  string email = "JohnDoe@gmail.com";
  person->set_email(email);
  string number = "032-9898-8765";
  Messages::Person::PhoneNumber* phone_number = person->add_phones();
  phone_number->set_number(number);
  phone_number->set_type(Messages::Person::MOBILE);
}



