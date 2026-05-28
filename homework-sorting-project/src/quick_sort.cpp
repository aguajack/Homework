#include "sorting.h"

#include <algorithm>
#include <vector>

using namespace std;

static int medianOfThreeIndex(vector<int>& arr, int left, int right)
{
    int mid = left + (right - left) / 2;

    int a = arr[left];
    int b = arr[mid];
    int c = arr[right];

    if ((a <= b && b <= c) || (c <= b && b <= a))
    {
        return mid;
    }
    else if ((b <= a && a <= c) || (c <= a && a <= b))
    {
        return left;
    }
    else
    {
        return right;
    }
}

static int partitionByMedianOfThree(vector<int>& arr, int left, int right)
{
    int pivotIndex = medianOfThreeIndex(arr, left, right);
    int pivot = arr[pivotIndex];

    swap(arr[pivotIndex], arr[right]);

    int storeIndex = left;

    for (int i = left; i < right; i++)
    {
        if (arr[i] < pivot)
        {
            swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }

    swap(arr[storeIndex], arr[right]);

    return storeIndex;
}

void quickSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int pivotIndex = partitionByMedianOfThree(arr, left, right);

    quickSort(arr, left, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, right);
}
