//Nicholas Fong
//COEN 177 Lab 1

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
int main(){
	cout<<"Shell Start\n";
	char input[100];
	while(1){
		cout<<"Enter a command: ";
		cin>>input;
		//close the program if exit command is typed in
		if(strcmp(input, "exit") == 0){
			return 0;
		}
		if(fork() != 0){	//fork off child process
			//parent code
			waitpid(-1, NULL, 0); //wait for child
		}
		else{	//child code
			execve(input, NULL, 0); //execute code
		}
	}
	return 0;
}
	

