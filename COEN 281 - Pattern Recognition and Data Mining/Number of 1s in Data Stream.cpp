// Nicholas Fong
// 10/14/17 (last edit date)
// COEN 281
// P2

// Online resources used for code examples:
// http://www.binarytides.com/socket-programming-c-linux-tutorial/
// http://www.linuxhowtos.org/data/6/client.c

/* This program assumes that queries for k bits will fail if k > than the number
 * of bits read in from the socket.
 * Also, queries must exactly match the form 
 * "What is the number of ones for last <k> data?" where k is a positive integer
 * greater than 0 and less than the number of bits seen.
 */

// some of these are probably useless that I forgot to delete after testing
#include <sys/socket.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <netinet/in.h> // for sockaddr_in server
#include <netdb.h> // for gethostbyname
#include <string.h> // for memcpy
#include <stdio.h>
#include <thread>
#include <arpa/inet.h>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <termios.h>
#include <deque>

using namespace std;

struct block{
    long long oldestBit;
    long long size;
};

// shared global variables for all threads to access
mutex newDataMtx;
bool dataStillFlowing = true;
deque<string> windowData;
string nullString;
deque<block> blockList;
long long bitsParsed = 0;
long long mostRecentOneTimestamp = 0;

// These functions that search through a deque of blocks assumes that newer
// blocks are added to the end of the deque where index 0 is the oldest block

// find the oldest block of size n for merging purposes
int indexOfOldestSizeNBlock(deque<block> d, long long n){
    int i;
    for(i = 0; i < d.size(); i++){
        if(d[i].size == n){
            break;
        }
    }
    return i;
}

// count the number of blocks of a given size
int numberOfSizeNBlocks(deque<block> d, long long n){
    deque<block>::size_type i = indexOfOldestSizeNBlock(d, n);
    int count = 0;
    for(i; i < min(d.size(), i+3); i++){
        if(d[i].size == n){
            count++;
        } else{
            break;
        }
    }
    return count;
}

// if there are too many blocks of the same size, merge the 2 oldest ones
void mergeSizeNBlocks(deque<block> &d, long long n){
    if(numberOfSizeNBlocks(d, n) > 3){
        int index = indexOfOldestSizeNBlock(d, n);
        block merged;
        merged.oldestBit = d[index].oldestBit;
        merged.size = d[index].size * 2;
        deque<block>::iterator it = d.begin() + index + 1;
        d.erase(it);
        it = d.begin() + index;
        d.erase(it);
        it = d.begin() + index;
        d.insert(it, merged);
        mergeSizeNBlocks(d, n*2);
    }
}

// add a new block with a single 1
void addOne(deque<block> &d, long long oldestBit){
    block one;
    one.size = 1;
    one.oldestBit = oldestBit;
    d.push_back(one);
    mergeSizeNBlocks(d, 1);
}

// print out the blocks from the DGIM algm for testing purposes
void printDeque(deque<block> d){
    for(int i = 0; i < d.size(); i++){
        cout << "Block " << i << " Oldest Bit: " << d[i].oldestBit << " Size: "
                << d[i].size << endl;
    }
    cout << endl;
}

// counts the exact number of 1s assuming that k is within the window size
long long countOnesInWindow(long long k){
    if(k > windowData.size()){
        return -1;
    }
    long long count = 0;
    for(long long i = windowData.size() - 1; i >= windowData.size() - k; i--){
        if(windowData[i] == "1"){
            count++;
        }
    }
    return count;
}

// estimates the number of 1s with less than 33% error
long long countOnesUsingDGIM(long long timestampToCountUntil){
    if(timestampToCountUntil < 0){
        return -1;
    }
    long long count = 0;
    for(int i = blockList.size(); i >= 0; i--){
        if(blockList[i].oldestBit <= timestampToCountUntil){
            count += blockList[i].size / 2;
            return count;
        } else{
            count += blockList[i].size;
        }
    }
    return count;
}

// return the number of 1s since time n
long long queryData(long long k){
    if(k > bitsParsed){
        return -1;
    }
    if(k < windowData.size()){
        return countOnesInWindow(k);
    }
    long long timestampToCountUntil = bitsParsed - k;
    return countOnesUsingDGIM(timestampToCountUntil);
}

// Source: https://stackoverflow.com/a/217605
// Trim removes whitespace
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

// Assume comments are delimited by #
// Credits to https://stackoverflow.com/a/10392453
string catchWhitespace(string input){
    input = input.substr(0, input.find("#", 0));
    input = trim(input);
    return input;
}

// Turns a character into a string
string charToString(char input){
    stringstream ss;
    string output;
    ss << input;
    ss >> output;
    return output;
}

// print out the values for testing purposes
void printDeque(deque<string> d){
    for(int i = 0; i < d.size(); i++){
        cout << d[i];
    }
    cout << endl;
    return;
}

// Credits to http://www.cplusplus.com/forum/articles/9645/
// return value of -1 indicates error
int strToInt(string s){
    int output;
    stringstream converter(s);
    stringstream test;
    converter >> output;
    if(converter.fail()){
        return -1;
    }
    test << output;         // this part is to catch if there is a number
    if(test.str() != s){    // followed by other stuff on the line
        return -1;
    }
    return output;
}

void getInputData(string hostName, int portNumber, int windowSize){
    int socketDesc, hostSuccessFlag;
    struct sockaddr_in serverAddress;
    struct hostent *server;
    char serverReply[1];
    string bit;
    string one = "1";
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDesc < -1){
        cout << "ERROR: Could not create socket\n";
        exit(1);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    hostSuccessFlag = inet_pton(AF_INET, hostName.c_str(), &(serverAddress.sin_addr));
    if(hostSuccessFlag != 1){
        server = gethostbyname(hostName.c_str());
        if(server == NULL){
            cout << "ERROR: no such host\n";
            exit(1);
        }
        // memcpy source: https://stackoverflow.com/a/5445610
        memcpy(&serverAddress.sin_addr, server->h_addr_list[0], server->h_length);
    }
    
    if(connect(socketDesc, (struct sockaddr *)&serverAddress, sizeof(serverAddress))){
        cout << "ERROR: Could not connect to socket\n";
        exit(1);
    }
    while(recv(socketDesc, serverReply, 1, 0) > 0){
        bit = catchWhitespace(charToString(serverReply[0]));
        newDataMtx.lock();
        if(bit != nullString){
            bitsParsed++;
            if(windowData.size() >= windowSize){
                windowData.pop_front();
            }
            windowData.push_back(bit);
            if(bit == one){
                addOne(blockList, mostRecentOneTimestamp + 1);
                mostRecentOneTimestamp = bitsParsed;
            }
            cout << bit;
            cout.flush();
        }
        newDataMtx.unlock();
    }
    newDataMtx.lock();
    cout.flush();
    cout << endl;
    newDataMtx.unlock();
    dataStillFlowing = false;
    pthread_exit(NULL);
}

void getUserQuery(){
    string query, queryBeginning, queryEnd, queryK, exact;
    long long k, answer;
    while(getline(cin, query)){
        newDataMtx.lock();
        query = catchWhitespace(query);
        if(query.length() < 40){
            cout << "\nWARNING: Input query must exactly be of the form \"What is the number of ones for last <k> data?\"\n";
            newDataMtx.unlock();
            if(dataStillFlowing == false){
                pthread_exit(NULL);
            }
            continue;
        } else{
            cout << endl << query << endl;
            cout.flush();
        }
        newDataMtx.unlock();
        queryBeginning = query.substr(0,35);
        size_t endSpot = query.find("data");
        queryEnd = query.substr(endSpot);
        queryK = query.substr(35, endSpot - 35);
        queryK = trim(queryK);
        k = atoll(queryK.c_str());
        if(queryBeginning != "What is the number of ones for last"
                || queryEnd != "data?"
                || k <= 0){
            newDataMtx.lock();
            cout << "\nWARNING: Input query must exactly be of the form \"What is the number of ones for last <k> data?\"\n";
        } else{
            answer = queryData(k);
            if(k <= windowData.size()){
                exact = "exactly ";
            } else{
                exact = "estimated ";
            }
            newDataMtx.lock();
            if(answer == -1){
                cout << "\nERROR: Invalid k input\n";
            } else{
                cout << "\nThe number of ones of last " << k << " data is " << exact << answer << ".\n";
            }
        }
        //cout.flush();
        newDataMtx.unlock();
        if(dataStillFlowing == false){
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int portNumber, windowSize;
    string hostName, inputLine;
    //Get window size
    while(inputLine == nullString){
        if(cin.eof()){
            cout << "No input data\n";
            return 1;
        }
        getline(cin, inputLine);
        inputLine = catchWhitespace(inputLine);
        if(inputLine != nullString){
            windowSize = strToInt(inputLine);
            if(windowSize < 0){
                cout << "Error: Non-positive integer values entered into s\n";
                return 1;
            }
        }
    }
    inputLine = nullString; //reset values
    //Get host:port pair
    while(inputLine == nullString){
        if(cin.eof()){
            cout << "Error: No host:port pair entered\n";
            return 1;
        }
        getline(cin, inputLine);
        inputLine = catchWhitespace(inputLine);
        if(inputLine != nullString){
            string::size_type pos = inputLine.find(':');
            if(pos != string::npos){
                hostName = inputLine.substr(0, pos);
                hostName = catchWhitespace(hostName);
                portNumber = strToInt(catchWhitespace(inputLine.substr(pos+1)));
            } else{
                cout << "Error: Invalid host:port pair entered";
            }
        }
    }
    
    // set default values for testing
    /*hostName = "localhost";
    portNumber = 59289;
    windowSize = 1000;*/
    
    thread getData(getInputData, hostName, portNumber, windowSize);
    thread getQuery(getUserQuery);
    getData.join();
    getQuery.join();
    return 0;
}