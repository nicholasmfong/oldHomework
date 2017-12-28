#include <iostream>     //Nicholas Fong CSCI 61 HW 2 Problem 2
#include <algorithm>
using namespace std;
double total_comparisons = 0;       //total comparisons for permutations of size n to calculate the average
int max_comparisons = 0;            //biggest number of comparisons for a given permutation of size n
int compares = 0;                   //the number of comparisons for that specific permutation
vector<int> v;                      //generates the different permutations
int duplicate[11];                  //copy of the permutation to sort in array form for merge_sort
size_t counter = 0;                 //remembers which size permutation it is in across functions
template <class T, class SizeType>  //merges an array
void merge(T A[], SizeType lo, SizeType mid, SizeType hi){
    SizeType n(hi-lo+1);
    T *temp = new T[n];
    SizeType i(lo), j(mid+1);
    for (SizeType k = 0; k < n; ++k){
        if (i > mid){
            temp[k] = A[j++];
        }
        else if (j > hi){
            temp[k] = A[i++];
        }
        else if (A[j] < A[i]){
            temp[k] = A[j++];
            compares += 1;
        }
        else{
            temp[k] = A[i++];
            compares += 1;
        }
    }
    std::copy(temp, temp+n, A+lo);
}
template <class T, class SizeType>
void merge_sort(T A[], SizeType lo, SizeType hi){
    if (lo < hi){
        SizeType mid = (lo + hi)/2;
        merge_sort(A, lo, mid);
        merge_sort(A, mid+1, hi);
        merge(A, lo, mid, hi);
    }
}
void generate_permutations(size_t n){
    if (n == 1){
        compares = 0;
        for(size_t r = 0; r <= counter; r++){       //copies the permutation into an array so that merge_sort can work
            duplicate[r] = v[r];                    //and so that the merging doesn't mess up the generation of permutations
        }
        size_t zero = 0;                            //workaround so that merge_sort will be called by the same type of variable
        merge_sort(duplicate, zero, counter-1);
        total_comparisons += compares;
        if(compares > max_comparisons){
            max_comparisons = compares;
        }
        return;
    }
    for (size_t i = 0; i < n; ++i){
        swap(v[i], v[n-1]);
        generate_permutations(n-1);
        swap(v[i], v[n-1]);
    }
}
int main(){
    for (size_t count = 1; count <= 10; count++){
        v.clear();
        total_comparisons = 0;
        max_comparisons = 0;
        counter = count;
        for (size_t i = 1; i <= count; ++i){
            v.push_back(i);
        }
        generate_permutations(count);
        for(double i = count; i > 1; i--){          //calculates the average number of comparisons
            total_comparisons /= i;
        }
        cout<<"For size "<<count<<" the max number of comparisons is "<<max_comparisons<<endl<<     //outputs results
              "The average number of comparisons is "<<total_comparisons<<endl<<endl;
    }
    return 0;
}
