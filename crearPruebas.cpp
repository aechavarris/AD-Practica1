#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <random>

using namespace std;

//This funtion has been taken from here: https://stackoverflow.com/questions/21237905/how-do-i-generate-thread-safe-uniform-random-numbers
int intRand(const int & min, const int & max) {
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    // default_random_engine generator (seed);
    // uniform_int_distribution<int> distribution(min, max);
    return min + rand() % max;
}

int main(int argv, char* argc[]) {
    int minDim ;
    int maxDim ;
    int sum ;
    if (argv < 2) {
        cout << "Not enought arguments!" << endl;
        exit(1);
    }else if(argv == 2){
        minDim = atoi(argc[1]); 
        maxDim = minDim;
        sum =1; 
    }else if(argv == 3){
        minDim = atoi(argc[1]); 
        maxDim = atoi(argc[2]);
        sum = 1;
    }else if(argv == 4){
        minDim = atoi(argc[1]);
        maxDim = atoi(argc[2]);
        sum = atoi(argc[3]);
    }
    
    while(minDim <= maxDim){
        cout << "Creando grafo dimension "<< minDim <<endl;
        string para = to_string(minDim);
        string buffer = para + "\n";
        int** m;
        m = new int*[minDim];
        for (int i = 0; i < minDim; i++) {
            m[i] = new int[minDim];
        }

        ofstream MyFile("prueba_" + to_string(minDim) + ".txt");
        int i = 0;
        while(i < minDim){
            bool next = false;
            for (int j = 0; j < minDim; j++) {
                if (i != j) {
                    if (intRand(0, 100) > 50) {
                        m[i][j] = 1;
                        m[j][i] = 1;
                        next = true;
                    }else{
                        m[i][j] = 0;
                        m[j][i] = 0;
                    }
                }else{
                    m[i][j] = 0;
                    m[j][i] = 0;
                }
            }
            if(next){
                i++;
            }
        }
        for (int i = 0; i < minDim; i++) {
            for (int j = 0; j < minDim; j++) {
                if(m[i][j] == 1 || m[j][i]){
                    buffer = buffer + "1";
                }else{
                    buffer = buffer + "0";
                }
                if(j+1 <minDim ){
                    buffer= buffer + " ";
                }
            }
            buffer = buffer +"\n";
        }
        // Write to the file
        MyFile << buffer;

        // Close the file
        MyFile.close();
        for (int i = 0; i < minDim; i++) {
            delete m[i];
        }
        delete m;
        minDim = minDim + sum * minDim;
        if(minDim>maxDim){
            minDim = maxDim;
        }
        
    }
    return 0;
}
