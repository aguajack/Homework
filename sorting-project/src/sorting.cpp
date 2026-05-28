#include "sorting.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace std;

bool isSorted(const vector<int>& arr)
{
    for (int i = 1; i < static_cast<int>(arr.size()); i++)
    {
        if (arr[i - 1] > arr[i])
        {
            return false;
        }
    }
    return true;
}

void insertionSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

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

static void mergeBlocks(vector<int>& arr, vector<int>& temp, int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i < mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j < right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int index = left; index < right; index++)
    {
        arr[index] = temp[index];
    }
}

void iterativeMergeSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    if (n <= 1)
    {
        return;
    }

    vector<int> temp(n);

    for (int width = 1; width < n; width *= 2)
    {
        for (int left = 0; left < n; left += 2 * width)
        {
            int mid = min(left + width, n);
            int right = min(left + 2 * width, n);

            mergeBlocks(arr, temp, left, mid, right);
        }
    }
}

static void heapify(vector<int>& arr, int n, int root)
{
    int largest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    if (leftChild < n && arr[leftChild] > arr[largest])
    {
        largest = leftChild;
    }

    if (rightChild < n && arr[rightChild] > arr[largest])
    {
        largest = rightChild;
    }

    if (largest != root)
    {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void compositeSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    // TODO:
    // Change these thresholds after collecting your experimental results.
    // Example:
    // if small n is faster with Insertion Sort, keep it here.
    // if large n is faster with Merge Sort or Heap Sort, replace Quick Sort below.
    if (n <= 32)
    {
        insertionSort(arr);
    }
    else
    {
        quickSort(arr, 0, n - 1);
    }
}
