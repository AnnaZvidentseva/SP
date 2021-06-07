#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <memory.h>

int main()
{
	int s = socket(AF_INET, SOCK_STREAM,0);
	if (s<0)
	{
		perror("Error calling socket");
		return 0;
	}
	
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1433);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	int result = connect(s, (struct sockaddr *)&peer, sizeof(peer));
	if (result)
	{
		perror("Error calling connect");
		return 0;
	}
	
	char buf[] = "Hello, World!";
	result = send(s, "Hello, World!", 13, 0);
	if (result <= 0)
	{
		perror("Error calling send");
		return 0;
	}
	
	if (shutdown(s, 1) < 0)
	{
		perror("Error calling shutdown");
		return 0;
	}
	
	char buffer[20];
	memset(buffer, 0, 20*sizeof(char));
	int res = recv(s, buffer, sizeof(buffer)-1, 0);
	if (res < 0)
	{
		perror("Error calling recv");
		return 0;
	}
	if (res == 0)
	{
		perror("Server disconnected");
		return 0;
	}
	if (strncmp(buffer, "Hi, Dear!", 9) == 0)
	{
		printf("Got answer, Success.\n");
		printf("%s\n", buffer);
	}
	else 
		perror("Wrong answer!");

	return 0;
}
