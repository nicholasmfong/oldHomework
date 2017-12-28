#include <iostream>     //Nicholas Fong HW3
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;
int main()
{
    map <string,int> count;
    ifstream input;
    string file;
    cout<<"What file do you want to count the words of?\n";
    cout<<"anna_karenina.txt, don_quixote.txt, short.txt\n";
    cin>>file;
    file = "C:\\Qt\\Docs\\HW3\\" + file;    //to simplify file input typing
    input.open(file);
    if(input.fail()){
        cout<<"Input file opening failed\n";
        exit(1);
    }
    string temp;
    while (input >> temp)   //counts the words
    {
        count[temp]++;
    }
    vector <pair<int,string>> words;    //puts the map into a vector
    for(auto element:count){
        words.push_back(pair<int,string>(element.second,element.first));
    }
    for(int i=0; i<words.size()-1;i++){     //sorts the vector
        for(int j=i+1;j<words.size();j++){
            if(words[j].first>words[i].first){
                swap(words[i],words[j]);
            }
        }
    }
    for(int k=0;k<20 && k<words.size();k++){    //prints the 20 most used words
        cout<<words[k].first<<" "<<words[k].second<<endl;
    }
    input.close();
    return 0;
}
