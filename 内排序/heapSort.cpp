# include <iostream>
# include <vector>
using namespace::std;
void sink(vector<int>& a, int k, int n);
void exch(vector<int>& a, int i, int j);
void print(vector<int>& a);
void sink(vector<int>& a, int k, int n){ // k:the index to sink n:the length of array
    while(2*k+1<n){ // left leaf is 2k+1, right leaf is 2k+2
        int j = 2*k + 1; 
        if(j<n-1&&a[j]<a[j+1]) j++; // if left leaf is less than right leaf, j++
        if(a[k]>a[j]) break; 
        exch(a,k,j); // ensure that top of every three nodes is biggest
        k = j;  // continue to sink
    }
}

void exch(vector<int>& a, int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp; 
}

void heapSort(vector<int>& a){
    int n = (int) a.size();
    for(int k = n/2 - 1;k>=0;k--){
        sink(a,k,n);
    }
    print(a);
    cout << "heap constructed";
    int k = n - 1;
    while(k>0){
        exch(a,k--,0);
        sink(a,0,k);
        print(a);
    }
}
void print(vector<int>& a){
    cout << endl;
    for(auto i:a){
        cout << i << " ";
    }
}
int main(){
    vector<int> a{46,74,16,53,14,26,40,53,86,65,27,34};
    heapSort(a);
    print(a);
}