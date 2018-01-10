/*Nicholas Fong COEN 177 Assignment 3 LRU Algorithm*/

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
  int leastRecentlyUsedPage;
  string input;
  stringstream ss;
  bool foundPage = false;
  vector<int> pagesInMemory;	//keeps track of the page value
  vector<int> pageUseTime;	//time the page was used
  
  //make the page vectors the right size
  for(int i = 0; i < pageCount; i++){
    pagesInMemory.push_back(0);	//0 means free memory/default value
    pageUseTime.push_back(0);
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
	  pagesInMemory[i] = pageInput;	//write the value in case it was the default 0
	  pageUseTime[i] = pageRequests;	//update the time of use
	  foundPage = true;	//tell us the page is used
	  break;
	}
      }	//end for loop
      
      if(foundPage == false){	//page fault
	pageFaults++;
	//find the page with the smallest pageUseTime and replace it
	leastRecentlyUsedPage = 0;	//location of page to kick out in page table
	for(int i = 1; i < pageCount; i++){
	  if(pageUseTime[i] < pageUseTime[leastRecentlyUsedPage]){
	    leastRecentlyUsedPage = i;
	  }
	}
	//replace the least recently used page with a new page
	pagesInMemory[leastRecentlyUsedPage] = pageInput;
	pageUseTime[leastRecentlyUsedPage] = pageRequests;
      }	//end page fault
      
    }	//end if found successful page value
    /*if(input == "end program"){	//to test program
      break;
    }*/
  }	//end while loop for input
  
  cout<<"Page Requests: "<<pageRequests<<endl;
  cout<<"Page Faults: "<<pageFaults<<endl;
  return 0;
}