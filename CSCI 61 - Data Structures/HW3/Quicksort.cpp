#include <iostream>         //Nicholas Fong HW 3 Problem 2
#include <algorithm>
using namespace std;
double total_comparisons = 0;       //total comparisons for permutations of size n to calculate the average
int max_comparisons = 0;            //biggest number of comparisons for a given permutation of size n
int compares = 0;                   //the number of comparisons for that specific permutation
vector<int> v;                      //generates the different permutations
vector<int> duplicate;              //copy of the permutation to sort in array form for merge_sort
int counter = 0;                    //remembers which size permutation it is in across functions
ostream & operator <<(ostream & os,const vector<int> & v){
    for (auto e: v)
        os << e << " ";
    return os;
}
template <class T, class SizeType>
SizeType partition(vector<T> &A, SizeType lo, SizeType hi){
    SizeType i(lo), j;
    for (j = lo; j < hi; ++j){
        compares++;
        if (A[j] < A[hi]){
            swap(A[j], A[i++]);
        }
    }
    swap(A[hi], A[i]);
    return i;
}
template <class T, class SizeType>
void quick_sort(vector<T> &A, SizeType lo, SizeType hi){
    if (hi <= lo){
        return;
    }
    SizeType p = partition(A, lo, hi);
    quick_sort(A, lo, p-1);
    quick_sort(A, p+1, hi);
}
void generate_permutations(int n){
    if (n == 1){
        duplicate.clear();
        compares = 0;
        for(unsigned int e = 0; e < v.size(); e++){
            duplicate.push_back(v[e]);
        }
        quick_sort(duplicate, 0, counter-1);
        total_comparisons += compares;
        if(compares > max_comparisons){
            max_comparisons = compares;
        }
        return;
    }
    for (int h = 0; h < n; ++h){
        swap(v[h], v[n-1]);
        generate_permutations(n-1);
        swap(v[h], v[n-1]);
    }
}
int main(){
    for(int i = 1; i <= 10; i++){
        v.clear();
        total_comparisons = 0;
        max_comparisons = 0;
        counter = i;
        for(int j = 1; j <= i; j++){
            v.push_back(j);
        }
        generate_permutations(i);
        for(double k = i; k > 1; k--){          //calculates the average number of comparisons
            total_comparisons /= k;
        }
        cout<<"For size "<<i<<" the max number of comparisons is "<<max_comparisons<<endl<<     //outputs results
              "The average number of comparisons is "<<total_comparisons<<endl<<endl;
    }
    return 0;
}

