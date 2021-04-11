#include <unistd.h>
#include <sys/wait.h> 
#include <stdio.h> 
#include <iostream>

using namespace std;

int main(){
	int host1, host2, host3; 
	int stat, flag, flag1 = 0, flag2 = 0, flag3 = 0; 
	int num=254; 

	do 
	{
		cout<<"Введите первый октет IP-адреса (192-223): ";
		cin>>host1;
		if ((host1>191) && (host1<224))
			flag1 = 1;
	} while (flag1 == 0);
	do 
	{
		cout<<"Введите второй октет IP-адреса (1-254): ";
		cin>>host2;
		if ((host2>0) && (host2<255))
			flag2 = 1;
	} while (flag2 == 0);
	do 
	{
		cout<<"Введите третий октет IP-адреса (1-254): ";
		cin>>host3;
		if ((host3>0) && (host1<255))
			flag3 = 1;
	} while (flag3 == 0);
		
	int *pid = new int[num];
	for (int i = 0; i < num; i++)
	{ 
		pid[i] = fork(); 
		if (pid[i] == -1){ 
			cout << "Error" << endl; 
			exit(1);
		}
		else if(pid[i] == 0){ 
			execl("ping",(to_string(i+1)).c_str(), (to_string(host1)).c_str(), (to_string(host2)).c_str(), (to_string(host3)).c_str(), NULL); 
			exit(0); 
		}
	}
	do {
		flag = 0; 
		for (int i = 0; i < num; i++){ 
			if (waitpid(pid[i], &stat, WNOHANG) == 0) flag = 1; 
		}
	} while (flag == 1); 
	cout << "end" << endl; 
}
