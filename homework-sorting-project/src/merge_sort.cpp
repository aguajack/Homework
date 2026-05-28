#include "sorting.h"

#include <algorithm>
#include <vector>

using namespace std;

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
