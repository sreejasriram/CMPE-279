// Server side C/C++ program to demonstrate Socket programming
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
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char *hello = "Hello from server";
	pid_t current_pid;
	int privilegeSet=0;
	int err;
	

	printf("execve=0x%p\n", execve);

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
	current_pid=fork();
	if(current_pid==0){
		//child- fork() returns 0 in child
		printf("Running in Child\n");
		//reduce privileges
		int ret = execl("child", "child", &new_socket, hello, NULL);
		printf("%d",&ret);
		if (ret<0) {
			printf("exec failed");
			_exit(2);
		}
	}
	else if(current_pid>0){
	//parent- fork() returns child id in parent
		wait(2000);//parent should continue execution after child
		printf("Returned to Parent...\n");

	}
	else{
		perror("Unable to fork");
		_exit(2);
	}
	
	return 0;
}
