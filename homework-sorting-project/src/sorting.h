#ifndef SORTING_H
#define SORTING_H

#include <vector>

void insertionSort(std::vector<int>& arr);

void quickSort(std::vector<int>& arr, int left, int right);

void iterativeMergeSort(std::vector<int>& arr);

void heapSort(std::vector<int>& arr);

void compositeSort(std::vector<int>& arr);

bool isSorted(const std::vector<int>& arr);

#endif
