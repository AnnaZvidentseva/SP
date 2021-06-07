#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <errno.h>

int main ()
{
	int sock = socket(AF_INET, SOCK_STREAM,0);
	if (sock<0)
	{
		perror("Error calling socket");
		return 0;
	}
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1433);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Error calling bind");
		return 0;
	}
	
	if (listen(sock,5))
	{
		perror("Error calling listen");
		return 0;
	}
	while (1)
	{
		int sock_1 = accept(sock, NULL, NULL);
		if (sock_1 < 0)
		{
			perror("Error calling accept");
			return 0;
		}
		
		char buffer[30];
		int count = 0;
		for (;;)
		{
			memset(buffer, 0, sizeof(char)*31);
			int rc = recv(sock_1, buffer, 30, 0);
			if (rc < 0)
			{
				if (errno == EINTR)
					continue;
				perror("Can't receive data");
				return 0;
			}
			if (rc == 0)
				break;
			printf("%s\n", buffer);
		}
		char response[] = "Hi, Dear!";
		if (send(sock_1, response, sizeof(response), 0) < 0)
			perror("Error sending response");
		printf("Response send\n");
	}
	return 0;
}
