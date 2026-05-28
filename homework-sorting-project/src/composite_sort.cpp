#include "sorting.h"

#include <vector>

using namespace std;

void compositeSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    if (n <= 32)
    {
        insertionSort(arr);
    }
    else
    {
        quickSort(arr, 0, n - 1);
    }
}
