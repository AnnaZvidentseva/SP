#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <memory.h>

int main()
{
	int s = socket(AF_INET, SOCK_DGRAM, 0);
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
	result = sendto(s, "Hello, World!", 13, 0, (struct sockaddr *)&peer, sizeof(peer));

	return 0;
}
