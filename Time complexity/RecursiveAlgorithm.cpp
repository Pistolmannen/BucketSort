#include <iostream>
#include <cmath>

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
    int Answer = Timefunction(2);  // Start input
    
    cout << Answer; // Result
    
    return 0;
}