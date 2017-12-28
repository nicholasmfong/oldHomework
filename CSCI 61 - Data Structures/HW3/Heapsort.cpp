#include <iostream>         //Nicholas Fong HW 3 Problem 1
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
void heapify(vector<T> & A, SizeType n, SizeType r){
    SizeType lc = 2*r;
    if (lc > n){    // a leaf
        return;
    }
    if (lc < n){
        compares++;
        if(A[lc+1] > A[lc]){
            lc++;
        }
    }
    compares++;
    if (A[r] >= A[lc]){ // parent >= children; done
        return;
    }
    swap(A[r], A[lc]);
    heapify(A, n, lc);
}
template <class T, class SizeType>
void make_heap(vector<T> & A, SizeType n){
    for (SizeType r = n/2; r >= 1; --r){
        heapify(A, n, r);
    }
}
template <class T, class SizeType>
void heap_sort(vector<T> & A, SizeType n){
    make_heap(A, n);
    for (SizeType s = n; s > 1; s--){
        swap(A[1], A[s]);
        heapify(A, s-1, 1);
    }
}
void generate_permutations(int n){
    if (n == 1){
        duplicate.clear();
        compares = 0;
        //cout<<"permutation is "<<v<<endl;
        duplicate.push_back(0);
        for(unsigned int e = 0; e < v.size(); e++){
            duplicate.push_back(v[e]);
        }
        heap_sort(duplicate, counter);
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
