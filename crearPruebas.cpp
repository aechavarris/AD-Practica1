#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <random>
#include <mutex>
#include "lib/progressBar/ProgressBar.hpp"
using namespace std;

int intRand(const int & min, const int & max) { 
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    return min + rand() % max;
}

int main(int argv, char* argc[]) {
    // Declaración de variables
    int minDim ;
    int maxDim ;
    float sum ;

    if (argv < 2) {
        cout << "Usage: ./crearPruebas [minDimension] [maxDimension] [incremento]" << endl;
        exit(1);
    } else if (argv == 2) {
        minDim = atoi(argc[1]); 
        maxDim = minDim;
        sum = 1; 
    } else if (argv == 3) {
        minDim = atoi(argc[1]); 
        maxDim = atoi(argc[2]);
        sum = 1;
    } else if(argv == 4) {
        minDim = atoi(argc[1]);
        maxDim = atoi(argc[2]);
        sum = atof(argc[3]);
    }
    
    while (minDim <= maxDim) {
        cout << "Creando grafo dimension "<< minDim <<endl;
        string para = to_string(minDim);
        const int limit = minDim * 2 ;
        progresscpp::ProgressBar progressBar(limit, 70);
        int** m;
        m = new int*[minDim];
        for (int i = 0; i < minDim; i++) {
            m[i] = new int[minDim];
        }

        ofstream MyFile("prueba_" + to_string(minDim) + ".txt");
        
        MyFile << para + "\n";
        int i = 0;
        int count = 0;
        while (i < minDim) {
            bool next = false;
            for (int j = 0; j < minDim; j++) {
                if (i != j) {
                    if (intRand(0, 100) > 50) {
                        m[i][j] = 1;
                        m[j][i] = 1;
                        next = true;
                    }
                    else {
                        m[i][j] = 0;
                        m[j][i] = 0;
                    }
                }
                else {
                    m[i][j] = 0;
                    m[j][i] = 0;
                }
            }
            ++progressBar;
            progressBar.display();
            if (next) i++;
        }

        for (int i = 0; i < minDim; i++) {
            for (int j = 0; j < minDim; j++) {
                if (m[i][j] || m[j][i]) MyFile << "1" ;
                else MyFile << "0" ;

                if (j + 1 < minDim) MyFile << " ";
            }
            ++progressBar;
            progressBar.display();
            MyFile << "\n" ;
        }

        // Write to the file

        // Close the file
        MyFile.close();
        progressBar.done();
        for (int i = 0; i < minDim; i++) delete m[i];

        delete m;

        if (minDim == maxDim) break;

        minDim = minDim * sum;
        if (minDim > maxDim) minDim = maxDim;
    }
    return 0;
}
