# include <iostream>
# include <vector>
using namespace::std;

void swap(vector<int>& a, int i, int j); // 交换的辅助函数
void print(vector<int>& a); // 打印的辅助函数


void selectionSort(vector<int>& a){
    int n = a.size();
    for(int i = 0;i<n;i++){
        int min = i;
        for(int j = i+1;j<n;j++){
            if(a[j]<a[min]){min=j;}
        }
        swap(a,i,min);
        print(a);
    }
}

void swap(vector<int>& a, int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void print(vector<int>& a){
    cout << endl;
    for(auto i:a){
        cout << i << " ";
    }
}

int main(){
    vector<int> a{46,74,16,53,14,26,40,53,86,65,27,34};
    selectionSort(a);
}