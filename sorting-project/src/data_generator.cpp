#include "data_generator.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

vector<int> generateSortedData(int n)
{
    vector<int> data(n);

    for (int i = 0; i < n; i++)
    {
        data[i] = i + 1;
    }

    return data;
}

vector<int> generateReverseData(int n)
{
    vector<int> data(n);

    for (int i = 0; i < n; i++)
    {
        data[i] = n - i;
    }

    return data;
}

vector<int> generateRandomData(int n)
{
    vector<int> data = generateSortedData(n);

    static random_device rd;
    static mt19937 generator(rd());

    shuffle(data.begin(), data.end(), generator);

    return data;
}

static vector<int> buildMergeWorstCase(const vector<int>& data)
{
    int n = static_cast<int>(data.size());

    if (n <= 1)
    {
        return data;
    }

    vector<int> left;
    vector<int> right;

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            left.push_back(data[i]);
        }
        else
        {
            right.push_back(data[i]);
        }
    }

    left = buildMergeWorstCase(left);
    right = buildMergeWorstCase(right);

    vector<int> result;
    result.reserve(n);

    for (int value : left)
    {
        result.push_back(value);
    }

    for (int value : right)
    {
        result.push_back(value);
    }

    return result;
}

vector<int> generateMergeWorstCaseData(int n)
{
    vector<int> sortedData = generateSortedData(n);

    return buildMergeWorstCase(sortedData);
}
