#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>      //for if file opening failed
#include <vector>
#include <ctype.h>      //for tolower()
#include <algorithm>    //for reverse()
#include <map>
#include "table.h"
using namespace std;
map<string,pair<pair<size_t,size_t>,pair<size_t,size_t>>> answers;      //contains the answers
int main(){     //the first pair of size_t is the starting location, the 2nd pair is the end location
    ifstream puzzle("C:\\Qt\\Docs\\CSCI61_HW4\\puzzle.txt");
    ifstream dictionary("C:\\Qt\\Docs\\CSCI61_HW4\\words.txt");
    if(puzzle.fail() || dictionary.fail()){
        cout<<"Input file opening failed.\n";
        exit(1);
    }
    table<string, 600000> words;        //sets up the global variables
    vector<vector<char>> grid;
    string intermediate;
    vector<string> copy;
    vector<char> test;
    while(dictionary>>intermediate){
        for(size_t i = 0; i < intermediate.size(); i++){    //inputs the dictionary into a hash table
            intermediate[i] = (tolower(intermediate[i]));   //and makes them all lowercase for simplicity
        }
        words.insert(intermediate);
    }
    while(!puzzle.eof()){
        getline(puzzle,intermediate);
        for(size_t i = 0; i < intermediate.size(); i++){
            if(intermediate[i] != ' '){                     //sets up the puzzle grid as a vector of vectors
                intermediate[i] = tolower(intermediate[i]); //and sets them to be lowercase for simplicity
                test.push_back(intermediate[i]);            //grid[0][0] is top left corner
            }                                               //grid[n][0] is the bottom left corner
        }                                                   //where n is the height of the puzzle -1
        grid.push_back(test);
        test.clear();
    }
    for(size_t i = 0; i < grid.size(); i++){          //displays the grid
        for(size_t j = 0; j < grid[i].size(); j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    for(size_t i = 0; i < grid.size(); i++){            //i is the row, j is the position in the row (column)
        for(size_t j = 0; j < grid[i].size(); j++){     //k is to check the length of the row
            string ans = "";
            string backwards = "";
            for(size_t k = j; k < grid[i].size(); k++){ //checks for horizontal words in the grid
                ans += grid[i][k];
                backwards = ans;
                reverse(backwards.begin(), backwards.end());
                if(words.find(ans)){
                    answers.insert(make_pair(ans,make_pair(make_pair(i,j),make_pair(i,k))));
                }
                if(words.find(backwards)){
                    answers.insert(make_pair(backwards,make_pair(make_pair(i,k),make_pair(i,j))));
                }
            }
        }
    }
    for(size_t i = 0; i < grid[0].size(); i++){         //i is the column, j is the position in the column (row)
        for(size_t j = 0; j < grid.size(); j++){        //k is to check the length of the column
            string ans = "";                            //assumes a rectangular grid
            string backwards = "";
            for(size_t k = j; k < grid[0].size(); k++){ //checks for vertical words in the grid
                ans += grid[k][i];
                backwards = ans;
                reverse(backwards.begin(), backwards.end());
                if(words.find(ans)){
                    answers.insert(make_pair(ans,make_pair(make_pair(j,i),make_pair(k,i))));
                }
                if(words.find(backwards)){
                    answers.insert(make_pair(backwards,make_pair(make_pair(k,i),make_pair(j,i))));
                }
            }
        }
    }
    for(size_t i = 0; i < grid.size(); i++){            //i is the row, j is the position in the row (column)
        for(size_t j = 0; j < grid[0].size(); j++){     //k checks down the diagonal
            string ans = "";
            string backwards = "";                      //checks the down and right diagonals (\)
            for(size_t k = 0; ((i+k) < grid.size()) && ((j+k) < grid[0].size()); k++){
                ans += grid[i+k][j+k];
                backwards = ans;
                reverse(backwards.begin(), backwards.end());
                if(words.find(ans)){
                    answers.insert(make_pair(ans,make_pair(make_pair(i,j),make_pair(i+k,j+k))));
                }
                if(words.find(backwards)){
                    answers.insert(make_pair(backwards,make_pair(make_pair(i+k,j+k),make_pair(i,j))));
                }
            }
        }
    }
    for(int i = 0; i < grid.size(); i++){           //i is the row, j is the position in the row (column)
        for(int j = 0; j < grid[0].size(); j++){    //k checks up the diagonal
            string ans = "";
            string backwards = "";                  //checks the up and right diagonals (/)
            for(int k = 0; ((i-k) >= 0) && ((j+k) < grid[0].size()); k++){
                ans += grid[i-k][j+k];
                backwards = ans;
                reverse(backwards.begin(), backwards.end());
                if(words.find(ans)){
                    answers.insert(make_pair(ans,make_pair(make_pair(i,j),make_pair(i-k,j+k))));
                }
                if(words.find(backwards)){
                    answers.insert(make_pair(backwards,make_pair(make_pair(i-k,j+k),make_pair(i,j))));
                }
            }
        }
    }
    size_t counter = 0;                 //prints the results
    size_t counter2 = 0;
    for(auto & e: answers){
        counter++;
        if(e.first.size()>=6){
            cout<<e.first<<"       from ("<<e.second.first.first+1<<", "<<e.second.first.second+1<<
                ") to ("<<e.second.second.first+1<<", "<<e.second.second.second+1<<")\n";
            counter2++;
        }
    }
    cout<<"\nThere are "<<counter<<" words in this puzzle.\n";
    cout<<"And there are "<<counter2<<" words of length 6 or more in this puzzle.\n\n";
    puzzle.close();
    dictionary.close();
    return 0;
}

