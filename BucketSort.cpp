#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Initializing a vector with list of multiple values
    vector<int> v = {1, 4, 5, 3, 2};

    // Finding the maximum element in the vector v
    int k = *max_element(v.begin(), v.end());

    // Creating a vector w with size k + 1
    vector<int> w(k + 1);

    // Output the elements of vector v
    cout << "Elements of v in a sorted order: ";
    for (auto i : v)
        w[i] = i;

    for (auto i : w)
        if (i != 0){
            cout << i << " ";
        }
    
    return 0;
}