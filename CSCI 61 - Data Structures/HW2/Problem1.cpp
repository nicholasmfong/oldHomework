#include <iostream> //Nicholas Fong CSCI 61 HW 2 Problem 1
#include <vector>
#include <algorithm>
using namespace std;
size_t length;
size_t most_comparisons = 0;
size_t most_swaps = 0;
vector<int> v;
vector<vector<int>> permutations;
vector<vector<int>> sorted;
vector<int> comparisons;
vector<int> swaps;
ostream & operator <<(ostream & os,const vector<int> & v){      //outputs a vector
    os<<"{";
    for (int u = 0; u < v.size()-1; u++){
        os << v[u] << " ";
    }
    os<<v[v.size()-1]<<"}";
    return os;
}
void insertion_sort(vector<int>& A, int n, size_t iterate){
    size_t swapped = 0;
    size_t compares = 0;
    for (int i = 1; i < n; ++i){
        for (int j = i; j > 0; --j){
            compares++;
            if(A[j-1] > A[j]){
                swap(A[j-1], A[j]);
                swapped++;
            }
            else{
                break;
            }
        }
    }
    if (swapped > most_swaps){
        most_swaps = swapped;
    }
    if (compares > most_comparisons){
        most_comparisons = compares;
    }
    swaps[iterate] = swapped;
    comparisons[iterate] = compares;
}
void generate_permutations(size_t n){
    if (n == 1){
        permutations.push_back(v);
        sorted.push_back(v);
        return;
    }
    for (size_t i = 0; i < n; ++i){
        swap(v[i], v[n-1]);
        generate_permutations(n-1);
        swap(v[i], v[n-1]);
    }
}
int main(){
    for(size_t n = 1; n <= 10; n++){
        length = n;
        v.clear();
        permutations.clear();
        sorted.clear();
        comparisons.clear();
        swaps.clear();
        most_comparisons = 0;
        most_swaps = 0;
        for (size_t i = 1; i <= n; ++i){
            v.push_back(i);
        }
        generate_permutations(n);
        for(size_t p = 0; p < permutations.size(); p++){            //initalizes the vectors
            comparisons.push_back(0);
            swaps.push_back(0);
        }
        for(size_t k = 0; k < permutations.size(); k++){                //sorts each permutation
            insertion_sort(sorted[k],length,k);
        }
        cout<<"For size = "<<n<<", Max number of swaps ="<<most_swaps<<endl;
        for(size_t elem = 0; elem < permutations.size(); elem++){
            if(swaps[elem] == most_swaps){
                cout<<permutations[elem]<<endl;
            }
        }
        size_t counter = 0;
        cout<<"Max number of comparisons ="<<most_comparisons<<endl;
        for(size_t it = 0; it < permutations.size(); it++){
            if (comparisons[it] == most_comparisons){
                cout<<permutations[it];
                counter++;
            }
        }
        cout<<" Count ="<<counter<<endl<<endl;
    }
    return 0;
}
