#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;

int Timefunction(float n, vector<int> calculatedValues){
    if (n == 1){        // If current result equals one
        return(1);
    }

    int partOne;
    int partTwo;

    if (calculatedValues[n-1] == NULL){ // If the current result doesn't exist in the vector
        partOne = Timefunction(n-1, calculatedValues);  // Calculates result
        calculatedValues.insert(calculatedValues.begin() + (n-1), partOne);  // Save result on a specific index
    }
    else{       // If the current result exists in the vector
        partOne = calculatedValues[n-1];
    }

    if (calculatedValues[ceil(n/2)] == NULL){   // If the current result doesn't exist in the vector
        partTwo = Timefunction(ceil(n/2), calculatedValues);    // Calculates result
        calculatedValues.insert(calculatedValues.begin() + ceil(n/2) , partTwo);    // Save result on a specific index
    }
    else{       // If the current result exists in the vector
        partTwo = calculatedValues[ceil(n/2)];
    }
    
    int answer = (partOne + partTwo + n);  // Puts the results together
    
    return(answer); // Returns the result for the current function-iteration 
}

int main(int argc, char const *argv[]){ 

    auto start = chrono::high_resolution_clock::now(); 

    float inputValue = 200; // Input value

    vector<int> calculatedValues(inputValue); // Creates a vector with the size of the inputed value
    
    int answer = Timefunction(inputValue, calculatedValues);  // Start function-iterations

    auto end = chrono::high_resolution_clock::now(); 

    chrono::milliseconds spentTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << answer << " time spent: " << spentTime.count(); // Result from all function-interations
    
    return 0;
}