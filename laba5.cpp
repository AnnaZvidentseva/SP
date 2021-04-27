#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <mutex>
#include <cstdlib>
#include <fstream>
using namespace std;

ofstream out;

pthread_mutex_t m;

struct data { 
    int h1;
    int h2;
    int h3;
    int h4;
};

void *ipPing (void *arg){
	data *h;
	h = (struct data *) arg;    
	int host1 = h->h1;
	int host2 = h->h2;
	int host3 = h->h3;
	int host4 = h->h4;
	
	string host11=(to_string(host1)).c_str(), host22=(to_string(host2)).c_str(), host33=(to_string(host3)).c_str(), host44=(to_string(host4)).c_str();
	string hostip = host11 + "." + host22 + "." + host33 + "." + host44;
	
	pthread_mutex_lock(&m);
	out.open("logs", ios::app);
	out << "Host: " << hostip << " ";
	out.close();
	
	if (system(("ping " + hostip + " -c 2").c_str()) == 0)
	{
		out.open("logs", ios::app);
		out << "- Destination Host Reachable" << endl;
		out.close();
	}
	else
	{
		out.open("logs", ios::app);
		out << "- Destination Host Unreachable" << endl;
		out.close();
	}
	pthread_mutex_unlock(&m);
    
	pthread_exit(NULL);
}

int main(){
	pthread_mutex_init(&m,NULL);
	int num = 254, num1 = 254;
	int ip1=192, ip2=168, ip3=8, i=0;
	
	data *host = new data[num];
	pthread_t *pingip = new pthread_t[num];
		
	while (i < num/2)
	{
		host[i].h1 = ip1;
		host[i].h2 = ip2;
		host[i].h3 = ip3;
		host[i].h4 = i+1;
		pthread_create(&pingip[i], NULL, ipPing, (void *)&host[i]);
		i++;
		
		host[num1].h1 = ip1;
		host[num1].h2 = ip2;
		host[num1].h3 = ip3;
		host[num1].h4 = num1;
		pthread_create(&pingip[num1], NULL, ipPing, (void *)&host[num1]);
		num1--;
	}
	for(int i = 0; i < num; i++ )
        	pthread_join(pingip[i],NULL);
        cout << "END" << endl;
}	
