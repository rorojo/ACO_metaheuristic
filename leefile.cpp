// io/read-file-sum.cpp - Read integers from file and print sum.
// Fred Swartz 2003-08-20

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib> //exit
using namespace std;

int main() {
    int sumx = 0;
    int sumy = 0;
    int x;
    int y;
    ifstream inFile;
    
    inFile.open("city_data.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile){
    
        if (inFile >> x) {
                sumx = sumx + x;
        }
        if (inFile >> y) {
                sumy = sumy + y;
        }
    
    }
    
    
    inFile.close();
    cout << "Sumx = " << sumx << endl; 
    cout << "Sumy = " << sumy << endl; 
    return 0;
}
