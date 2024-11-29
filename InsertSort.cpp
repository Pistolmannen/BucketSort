#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void insertSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int compare = arr[i];
        int move = i - 1;

        while (move >= 0 && arr[move] > compare) {
            arr[move + 1] = arr[move];
            move = move - 1;
        }
        arr[move + 1] = compare;
    }
    
    cout << "Sorted vector: ";
    for (int i = 0; i < arr[i]; i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    // Initializing a vector with list of multiple values
    vector<int> v = {1, 4, 5, 3, 2}; 
    int n = v.size();

    cout << "Unsorted vector: ";

    for (int i = 0; i < n; ++i)
        cout << v[i] << " ";
    cout << endl;

    insertSort(v);

    return 0;
}