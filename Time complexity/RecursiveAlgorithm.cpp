#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int Timefunction(float n){
    if (n == 1){
        return(1);
    }
    
    int partOne = Timefunction(n-1);
    int partTwo = Timefunction(ceil(n/2));
    int answer = (partOne + partTwo + n);
    
    return(answer);
}

int main(int argc, char const *argv[]){ 
    int Answer = Timefunction(500);
    
    cout << Answer;
    
    return 0;
}