#include <iostream>
#include <vector>
#include <chrono> // For timing
#include <cstdlib> // For rand()
#include <omp.h> // OpenMP library

using namespace std;
using namespace std::chrono; // For timing

// Function to partition the array and return the index of the pivot element
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Select the pivot element (here, the last element)
    int i = low - 1; // Index of the smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of the smaller element
            swap(arr[i], arr[j]); // Swap arr[i] and arr[j]
        }
    }
    swap(arr[i + 1], arr[high]); // Swap the pivot element with the element at i+1
    return i + 1; // Return the index of the pivot element
}

// Function to perform quicksort
void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array and get the index of the pivot element
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after the pivot
#pragma omp parallel sections
        {
#pragma omp section
            quicksort(arr, low, pi - 1);
#pragma omp section
            quicksort(arr, pi + 1, high);
        }
    }
}

int main() {
    // Generate a large random array for testing
    const int n = 1000000;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000; // Random numbers between 0 and 999
    }

    // Measure the execution time of Quicksort
    auto start = high_resolution_clock::now();

    // Sort the array
    quicksort(arr, 0, n - 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Output the execution time
    cout << "Time taken for parallel Quicksort with OpenMP: " << duration.count() << " milliseconds" << endl;

    return 0;
}
