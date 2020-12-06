# include <iostream>
# include <vector>
using namespace std;
class QuickSort{
    private:
        void sort(vector<int>& a, int low, int high);
        void exch(vector<int>& a, int i, int j); 
    public:
        void sort(vector<int>& a);
        int partition(vector<int>& a, int low, int high); // insert the pivot into array at partition
        
};

void print(vector<int>& a);

int QuickSort::partition(vector<int>& a, int low, int high){
    int i = low;
    int j = high + 1;
    int v = a[low];
    while(true){
        while(a[++i]<v){
            if(i==high)break;
        }  // move left pointer i
        while(a[--j]>v){
            if(j==low)break;
        }  // move right pointer j
        if(i>=j)break; // if i and j meet, break
        exch(a,i,j);  // else exchange i and j to make elements on the left less than v and right greater than v;
    }
    exch(a,low,j); // insert pivot into the array
    return j;
}

void QuickSort::sort(vector<int>& a, int low, int high){
    if(high<=low)return;
    int k = partition(a,low,high); 
    print(a);
    sort(a,low,k-1); // recursively sort left half
    sort(a,k+1,high);  // recursively sort right half
}

void QuickSort::sort(vector<int>& a){
    sort(a,0,(int) a.size()-1);
}
void QuickSort::exch(vector<int>& a, int i, int j){
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
    QuickSort* qs = new QuickSort();
    vector<int> a{46,74,16,53,14,26,40,53,86,65,27,34};
    qs->sort(a);
}