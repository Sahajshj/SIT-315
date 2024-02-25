#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

int main() {
    const int size = 100000000;
    vector<int> v1(size), v2(size), v3(size); // Vectors for storing random numbers and result

    // Initialize v1 and v2 with random values
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        v1[i] = rand() % 100;
        v2[i] = rand() % 100;
    }

    auto start = chrono::high_resolution_clock::now();

    // Perform vector addition in parallel with guided scheduling
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < size; ++i) {
        v3[i] = v1[i] + v2[i];
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    // Output the execution time
    cout << "Time taken for vector addition with guided scheduling: " << duration.count() << " milliseconds" << endl;

    return 0;
}
