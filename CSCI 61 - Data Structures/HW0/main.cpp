#include <iostream>     //Nicholas Fong CSCI 61 HW 0
#include <queue>
#include <vector>
using namespace std;
int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    queue<vector<int>> q;           //produces the different sized combinations
    vector<int> empty;
    q.push(vector<int>());
    for(int i = 1; i <= n; i++){
        while(q.front() != empty){
            vector<int> f = q.front();
            vector<int> g = f;
            g.push_back(i);
            q.pop();
            q.push(g);
            q.push(f);
        }
        vector<int> f = q.front();      //perform the loop once more when we reach the empty vector
        vector<int> g = f;
        g.push_back(i);
        q.pop();
        q.push(g);
        q.push(f);
    }
    int count = 0;
    while (!q.empty()){      //writes the answers
        vector<int> f = q.front();
        q.pop();
        for (auto e: f)
            cout << e << " ";
        cout << endl;
        count++;
    }
    cout<<"Total combinations = "<<count<<endl;
}
