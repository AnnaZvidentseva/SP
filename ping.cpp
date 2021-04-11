#include <unistd.h>
#include <sys/wait.h> 
#include <stdio.h> 
#include <iostream>

using namespace std;
int main(int argc, char* argv[]){ 
	string i = argv[0];
	string host1 = argv[1];
	string host2 = argv[2];
	string host3 = argv[3]; 
	string host = host1 +"."+ host2 +"."+ host3 +"."+i;
	
	if (system(("ping  " + host + " -c 1").c_str()) == 0)
		cout<<host<<" Destination Host Reachable" << endl;
	else cout <<host<< " Destination Host Unreachable" << endl;
	sleep(1); 
	exit(0); 
}
