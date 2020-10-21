#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<errno.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
	int new_socket,privilegeSet,valread;
	char *hello;
	char buffer[1024] = {0};
	if(argc>1){
		new_socket = *argv[1];
		hello = argv[2];
	}else{
		printf("Invalid no. of arguments to child");
		exit(0);
	}
	privilegeSet = setuid(65534); 
	//printf("privilege Set: %d\n",privilegeSet);
	if(privilegeSet ==-1){
		printf("Error in reducing Privilege\n");
		return 0;
	}
	valread = read( new_socket , buffer, 1024);
	printf("%s\n",buffer );
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;
}
