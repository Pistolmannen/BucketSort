// C++ Program to initializ std::vector with
// initializer list
#include <iostream>
#include <vector>
using namespace std;

int main() {

    // Initializing std::vector with list of
    // multiple values
    vector<int> v = {11, 23, 45, 89};

    for (auto i : v)
        cout << i << " ";
    return 0;
}