//Nicholas Fong
//COEN 177 Lab 1

#include <iostream>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main(){
	
	pid_t masterId = getpid();
        pid_t mostRecentId = getpid();
	cout<<"This is the master with id "<<masterId<<endl;
        
	int counter = 8; //create 8 children
        while(counter > 0){
                pid_t pid = fork();
                if(pid){
                //each process only forks once because only the parent gets an id}
                	break;
		}
		counter-=1;
		mostRecentId = getpid();
	}
	fork();	//all 8 children will fork leaving 16 children
	if(getpid() == mostRecentId && counter == 0){
	// make sure the last child forks 3 times instead of once
		pid_t lastCheck = fork(); //get that one extra child
		if(lastCheck == getpid()){
			fork();
		}
	}
	if(getpid() == masterId){ //get the master to fork 3 times
		fork();
	}
	
	//leaving a total of 19 children
	
	//count processes
	cout<<"I am a process with id "<<getpid()<<" and parent id "<<getppid()<<endl;
        waitpid(-1, NULL, 0);//some processes were terminating early so this stops that
	return 0;
	
}
