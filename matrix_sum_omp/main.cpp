#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

void PrintMatrix(const string& name, double* pMatrix, int M) {
    if (M > 10) return;
    cout << "Matrix " << name << ":" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cout << setw(8) << fixed << setprecision(2) << pMatrix[i * M + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int M = 20000;

    double* pA = new double[M * M];
    double* pB = new double[M * M];
    double* pC = new double[M * M];

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < M * M; i++) {
        pA[i] = static_cast<double>(rand() % 1000) / 100.0;
        pB[i] = static_cast<double>(rand() % 1000) / 100.0;
    }

    int ThreadsNum = 6;
    omp_set_num_threads(ThreadsNum);

    if (ThreadsNum == 1) {
        cout << "Matrix Size: " << M << "x" << M << " Mode: Serial" << endl;
    }
    else {
        cout << "Matrix Size: " << M << "x" << M << " Mode: Parallel (OpenMP). Threads: " << ThreadsNum << endl;
    }

    PrintMatrix("A", pA, M);
    PrintMatrix("B", pB, M);

    double StartTime = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < M * M; i++) {
        pC[i] = pA[i] + pB[i];
    }

    double EndTime = omp_get_wtime();

    PrintMatrix("C (Result)", pC, M);
    cout << "Execution time: " << (EndTime - StartTime) << " sec." << endl;

    delete[] pA;
    delete[] pB;
    delete[] pC;

    return 0;
}