#include <iostream>     //Nicholas Fong CSCI 61 Section 2 HW 8
#include <fstream>      //for file input
#include <cstdlib>      //for exit(1)
#include <string>
#include <list>
#include "graph.h"
using namespace std;
int main(){
    graph g;
    ifstream input;
    input.open("C:\\Qt\\Docs\\CSCI61_HW8\\graph.txt");
    if(input.fail()){
        cout<<"Input file opening failed.\n";
        exit(1);
    }
    input >> g;
    list<size_t> test, team1, team2;
    bool works;
    works = g.make_teams(team1, team2);
    if(works){
        cout<<"Team 1 = ";
        for(auto a: team1){
            cout<<a<<" ";
        }
        cout<<"\nTeam 2 = ";
        for(auto b: team2){
            cout<<b<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"NOT POSSIBLE\n";
    }
    input.close();
    return 0;
}
