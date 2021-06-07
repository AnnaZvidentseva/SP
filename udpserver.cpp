#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <errno.h>

int main ()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
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
	
	while (1)
	{	
		char buffer[30];
		int count = 0;
		for (;;)
		{
			memset(buffer, 0, sizeof(char)*30);
			int rc = recvfrom(sock, buffer, 30, 0, NULL, NULL);
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
	}
	return 0;
}
