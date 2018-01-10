//Nicholas Fong
//COEN 177 Lab 1

#include <iostream>
#include <cstring>
#include <sys/wait.h>
 
using namespace std;

int main(){
	
	cout<<"This is the master with id "<<getpid()<<endl;
	int counter = 16; //create 16 children
	while(counter > 0){
		pid_t pid = fork();
		if(pid){ 	
		//each process only forks once because only the parent gets an id
			break;
		}
		counter--;
	}
	//count and display processes
	cout<<"I am a process with id "<<getpid()<<" and parent id "<<getppid()<<endl;
	waitpid(-1, NULL, 0);
	return 0;
}
