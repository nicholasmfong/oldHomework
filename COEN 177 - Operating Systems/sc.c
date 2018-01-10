/*Nicholas Fong COEN 177 Assignment 3 Second-Chance Algorithm*/

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>

using namespace std;
int main(int argc, char *argv[]){
  //pageCount is the number of pages in the page table
  int pageCount = atoi(argv[1]);	//atoi converts the input string into an int
  if(pageCount <= 0){	//make sure the input is good
    cout<<"Invalid page count value\n";
    return -1;
  }
  int pageRequests = 0;
  int pageFaults = 0;
  int pageInput;	//the requested page
  int frontOfQueue = 0;	//the page that is next set to be replaced if unreferenced
  string input;
  stringstream ss;
  bool foundPage = false;
  vector<int> pagesInMemory;	//keeps track of the page value
  vector<bool> referenced;	//referenced bit
  
  //make the page vectors the right size
  for(int i = 0; i < pageCount; i++){
    pagesInMemory.push_back(0);	//0 means free memory/default value
    referenced.push_back(false);
  }
  
  //Actual working program
  while(getline(cin, input)){
    stringstream ss(input);	//split up the input line
    ss >> pageInput;	//try to put the input into an int
    if(ss){	//if successful, use that int value
      pageRequests++;
      foundPage = false;	//will be used to test if the page is found in the page table
      
      for(int i = 0; i < pageCount; i++){	//loop through page table
	//if page in page table(memory)
	if(pagesInMemory[i] == pageInput){
	  referenced[i] = true;	//update the referenced bit
	  foundPage = true;	//tell us the page is used
	  break;
	}
      }	//end for loop
      
      if(foundPage == false){	//page fault
	pageFaults++;
	//find the first unreferenced page starting from the head of the queue
	while(referenced[frontOfQueue] == true){
	  referenced[frontOfQueue] = false;
	  frontOfQueue = (frontOfQueue + 1) % pageCount;	//loop back around for clock algorithm
	}
	
	//we found an unreferenced page, so replace the page and move the front of the queue
	pagesInMemory[frontOfQueue] = pageInput;
	referenced[frontOfQueue] = true;
	frontOfQueue = (frontOfQueue + 1) % pageCount;
      }	//end page fault
      
    }	//end if found successful page value
  }	//end while loop for input
  
  cout<<"Page Requests: "<<pageRequests<<endl;
  cout<<"Page Faults: "<<pageFaults<<endl;
  return 0;
}