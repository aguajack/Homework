#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "data_generator.h"
#include "sorting.h"

using namespace std;
using namespace chrono;

using SortFunction = function<void(vector<int>&)>;

static double measureTimeMilliseconds(const vector<int>& originalData, SortFunction sortFunction)
{
    vector<int> data = originalData;

    auto start = high_resolution_clock::now();

    sortFunction(data);

    auto end = high_resolution_clock::now();

    if (!isSorted(data))
    {
        throw runtime_error("Sorting failed. The result is not sorted.");
    }

    duration<double, milli> elapsed = end - start;

    return elapsed.count();
}

static void runCorrectnessTest()
{
    vector<int> testData = {5, 1, 4, 2, 3};

    vector<int> a = testData;
    insertionSort(a);
    if (!isSorted(a)) throw runtime_error("Insertion Sort correctness test failed.");

    vector<int> b = testData;
    quickSort(b, 0, static_cast<int>(b.size()) - 1);
    if (!isSorted(b)) throw runtime_error("Quick Sort correctness test failed.");

    vector<int> c = testData;
    iterativeMergeSort(c);
    if (!isSorted(c)) throw runtime_error("Merge Sort correctness test failed.");

    vector<int> d = testData;
    heapSort(d);
    if (!isSorted(d)) throw runtime_error("Heap Sort correctness test failed.");

    vector<int> e = testData;
    compositeSort(e);
    if (!isSorted(e)) throw runtime_error("Composite Sort correctness test failed.");

    cout << "Correctness test passed.\n";
}

static double getMaxRuntimeFromRandomTests(int n, int testCount, SortFunction sortFunction)
{
    double maxTime = 0.0;

    for (int i = 0; i < testCount; i++)
    {
        vector<int> data = generateRandomData(n);
        double currentTime = measureTimeMilliseconds(data, sortFunction);

        maxTime = max(maxTime, currentTime);
    }

    return maxTime;
}

static double getAverageRuntimeFromRandomTests(int n, int testCount, SortFunction sortFunction)
{
    double totalTime = 0.0;

    for (int i = 0; i < testCount; i++)
    {
        vector<int> data = generateRandomData(n);
        totalTime += measureTimeMilliseconds(data, sortFunction);
    }

    return totalTime / testCount;
}

static double getCompositeWorstApproximation(int n, int testCount)
{
    double maxTime = 0.0;

    vector<int> reverseData = generateReverseData(n);
    vector<int> mergeWorstData = generateMergeWorstCaseData(n);

    maxTime = max(maxTime, measureTimeMilliseconds(reverseData, [](vector<int>& arr) {
        compositeSort(arr);
    }));

    maxTime = max(maxTime, measureTimeMilliseconds(mergeWorstData, [](vector<int>& arr) {
        compositeSort(arr);
    }));

    for (int i = 0; i < testCount; i++)
    {
        vector<int> randomData = generateRandomData(n);

        maxTime = max(maxTime, measureTimeMilliseconds(randomData, [](vector<int>& arr) {
            compositeSort(arr);
        }));
    }

    return maxTime;
}

static void runWorstCaseExperiment(const vector<int>& sizes, int randomTestCount)
{
    ofstream file("data/worst_case_results.csv");

    file << fixed << setprecision(6);
    file << "n,insertion_sort,quick_sort,merge_sort,heap_sort,composite_sort\n";

    for (int n : sizes)
    {
        vector<int> insertionData = generateReverseData(n);
        vector<int> mergeData = generateMergeWorstCaseData(n);

        double insertionTime = measureTimeMilliseconds(insertionData, [](vector<int>& arr) {
            insertionSort(arr);
        });

        double quickTime = getMaxRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
        });

        double mergeTime = measureTimeMilliseconds(mergeData, [](vector<int>& arr) {
            iterativeMergeSort(arr);
        });

        double heapTime = getMaxRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            heapSort(arr);
        });

        double compositeTime = getCompositeWorstApproximation(n, randomTestCount);

        file << n << ","
             << insertionTime << ","
             << quickTime << ","
             << mergeTime << ","
             << heapTime << ","
             << compositeTime << "\n";

        cout << "[Worst Case] n = " << n << " finished.\n";
    }

    file.close();
}

static void runAverageCaseExperiment(const vector<int>& sizes, int randomTestCount)
{
    ofstream file("data/average_case_results.csv");

    file << fixed << setprecision(6);
    file << "n,insertion_sort,quick_sort,merge_sort,heap_sort,composite_sort\n";

    for (int n : sizes)
    {
        double insertionTime = getAverageRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            insertionSort(arr);
        });

        double quickTime = getAverageRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
        });

        double mergeTime = getAverageRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            iterativeMergeSort(arr);
        });

        double heapTime = getAverageRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            heapSort(arr);
        });

        double compositeTime = getAverageRuntimeFromRandomTests(n, randomTestCount, [](vector<int>& arr) {
            compositeSort(arr);
        });

        file << n << ","
             << insertionTime << ","
             << quickTime << ","
             << mergeTime << ","
             << heapTime << ","
             << compositeTime << "\n";

        cout << "[Average Case] n = " << n << " finished.\n";
    }

    file.close();
}

int main()
{
    try
    {
        filesystem::create_directories("data");

        vector<int> sizes = {500, 1000, 2000, 3000, 4000, 5000};

        // Assignment requirement:
        // Heap Sort and Quick Sort should use at least 10 random permutations
        // when approximating worst-case runtime.
        int randomTestCount = 10;

        runCorrectnessTest();

        runWorstCaseExperiment(sizes, randomTestCount);

        runAverageCaseExperiment(sizes, randomTestCount);

        cout << "\nAll experiments completed.\n";
        cout << "Results saved to:\n";
        cout << "data/worst_case_results.csv\n";
        cout << "data/average_case_results.csv\n";
    }
    catch (const exception& error)
    {
        cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
