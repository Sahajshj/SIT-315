#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

void randomVector(vector<int>& vector, int start, int end) {
    #pragma omp parallel for default(none) shared(vector, start, end)
    for (int i = start; i < end; i++) {
        vector[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
}

void parallelVectorAddition(const vector<int>& v1, const vector<int>& v2, vector<int>& result, int numThreads) {
    int chunkSize = v1.size() / numThreads;
    #pragma omp parallel for default(none) shared(v1, v2, result, chunkSize) num_threads(numThreads)
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? v1.size() : (i + 1) * chunkSize;
        for (int j = start; j < end; ++j) {
            result[j] = v1[j] + v2[j];
        }
    }
}

int main() {
    unsigned long size = 100000000;
    int numThreads = 4; // Number of threads

    vector<int> v1(size), v2(size), v3(size); // Vectors for storing random numbers and result

    srand(time(0)); // Seed for random number generation

    auto start = chrono::high_resolution_clock::now();

    // Generate random vectors v1 and v2 in parallel
    randomVector(v1, 0, size);
    randomVector(v2, 0, size);

    // Perform vector addition in parallel
    parallelVectorAddition(v1, v2, v3, numThreads);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    // Output the execution time
    cout << "Time taken for vector addition: " << duration.count() << " milliseconds" << endl;

    return 0;
}
