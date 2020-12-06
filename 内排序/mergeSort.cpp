# include <iostream>
# include <vector>
using namespace::std;

void merge(vector<int>&a, vector<int>& aux, int low, int mid, int high);
void sort(vector<int>& a, vector<int>& aux ,int low, int high);
void sort(vector<int> &a);
void print(vector<int>& a);
void partprint(vector<int>& a,int low, int high);

void merge(vector<int>&a, vector<int>& aux, int low, int mid, int high){
    int n = a.size();
    for(int i = 0;i<n;i++){
        aux[i] = a[i];
    }  // copy array a to aux
    int i = low;
    int j = mid+1;
    // recopy aux to a
    for(int k = low;k<=high;k++){
        if(i>mid) a[k] = aux[j++]; // left is empty
        else if(j>high) a[k] = aux[i++]; // right is empty
        else if(aux[j]>aux[i]) a[k] = aux[i++]; // copy the less one to a
        else a[k] = a[j++]; 
    }

}

void sort(vector<int>& a, vector<int>& aux ,int low, int high){
    if(high<=low) return; // only one element, directly return
    int mid = low + (high - low) / 2;
    sort(a,aux,low,mid);  // sort left half
    sort(a,aux,mid+1,high); // sort right half
    partprint(a,low,mid);
    partprint(a,mid+1,high);
    cout << endl;
    cout << "merge " << " low " << low << " mid " << mid << " high " << high << endl;
    merge(a, aux, low ,mid, high); // merge the sorted left half and the sorted right half
    print(a);
    cout << endl;
    cout << "---------------------" << endl;
}

void sort(vector<int>& a){
    vector<int> aux(a.size());
    sort(a,aux,0,(int)(a.size()-1));
}

// helper to print an array
void print(vector<int>& a){
    cout << endl;
    for(auto i:a){
        cout << i << " ";
    }
}
// helper to print part of an array
void partprint(vector<int>& a,int low, int high){
    cout << endl;
    for(int i = low;i<=high;i++){
        cout << a[i] << " ";
    }
}

int main(){
    vector<int> a{46,74,16,53,14,26,40,53,86,65,27,34};
    sort(a);
    print(a);
}