#include <iostream>
#include <cmath>
#include <chrono>


using namespace std;

int Timefunction(float n){
    if (n == 1){        // If current result equals one
        return(1);
    }
    
    int partOne = Timefunction(n-1);    // T(n-1)
    int partTwo = Timefunction(ceil(n/2));  // T([n/2])
    int answer = (partOne + partTwo + n);  // Puts the results together
    
    return(answer); // Returns the result for the current function-iteration 
}

int main(int argc, char const *argv[]){ 

    auto start = chrono::high_resolution_clock::now(); 

    float inputValue = 200; // Input value

    int Answer = Timefunction(inputValue);  // Start input

    auto end = chrono::high_resolution_clock::now(); 

    chrono::milliseconds spentTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << Answer << " time spent: " << spentTime.count(); // Result
    
    return 0;
}