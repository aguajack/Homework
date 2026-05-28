# Sorting Project

## 1. Project Description

This project implements and compares four sorting algorithms:

1. Insertion Sort
2. Quick Sort with median-of-three pivot selection
3. Iterative Merge Sort
4. Heap Sort

The goal is to measure the runtime of these algorithms under different input sizes and input conditions, then design a **Composite Sort** function that automatically selects a suitable sorting algorithm based on the input size.

---

## 2. Project Structure

```text
sorting-project/
│
├── README.md
├── .gitignore
├── Makefile
│
├── src/
│   ├── main.cpp
│   ├── sorting.h
│   ├── sorting.cpp
│   ├── data_generator.h
│   └── data_generator.cpp
│
├── data/
│   ├── worst_case_results.csv
│   ├── average_case_results.csv
│   └── README.md
│
├── charts/
│   ├── worst_case_chart.png
│   ├── average_case_chart.png
│   └── README.md
│
├── report/
│   └── sorting_project_report.md
│
├── scripts/
│   └── generate_charts.py
│
└── screenshots/
    └── README.md
```

---

## 3. Sorting Algorithms

### 3.1 Insertion Sort

Insertion Sort is efficient for small input sizes, but its worst-case time complexity is:

```text
O(n^2)
```

### 3.2 Quick Sort

This project uses Quick Sort with **median-of-three** pivot selection.

Average-case time complexity:

```text
O(n log n)
```

Worst-case time complexity:

```text
O(n^2)
```

### 3.3 Iterative Merge Sort

This project uses the iterative version of Merge Sort.

Time complexity:

```text
O(n log n)
```

### 3.4 Heap Sort

Heap Sort uses a heap data structure.

Time complexity:

```text
O(n log n)
```

---

## 4. Testing Method

The tested input sizes are:

```text
n = 500, 1000, 2000, 3000, 4000, 5000
```

For every sorting algorithm, the program first checks whether the sorting result is correct.

The runtime is measured using `std::chrono::high_resolution_clock`.

---

## 5. Worst-Case Runtime Test

### 5.1 Insertion Sort

The worst case of Insertion Sort is a reverse-sorted array.

Example:

```text
5 4 3 2 1
```

### 5.2 Merge Sort

A custom Merge Sort worst-case data generator is used.

### 5.3 Heap Sort

The worst case of Heap Sort is approximated by testing multiple random permutations.

For each input size, at least 10 random permutations are tested.  
The maximum runtime is selected as the approximate worst-case runtime.

### 5.4 Quick Sort

The worst case of Quick Sort is approximated by testing multiple random permutations.

For each input size, at least 10 random permutations are tested.  
The maximum runtime is selected as the approximate worst-case runtime.

---

## 6. Average-Case Runtime Test

For the average-case test, random permutations are used.

Each random permutation is used once.  
The average runtime is calculated from multiple random tests.

---

## 7. Composite Sort

The Composite Sort function selects a sorting algorithm based on input size.

Current default setting:

```cpp
if (n <= 32)
{
    insertionSort(arr);
}
else
{
    quickSort(arr, 0, n - 1);
}
```

After collecting real experimental results, the threshold values should be modified according to the runtime tables.

---

## 8. Runtime Results

### 8.1 Worst-Case Runtime Table

| n | Insertion Sort | Quick Sort | Merge Sort | Heap Sort | Composite Sort |
|---|---:|---:|---:|---:|---:|
| 500 |  |  |  |  |  |
| 1000 |  |  |  |  |  |
| 2000 |  |  |  |  |  |
| 3000 |  |  |  |  |  |
| 4000 |  |  |  |  |  |
| 5000 |  |  |  |  |  |

### 8.2 Average-Case Runtime Table

| n | Insertion Sort | Quick Sort | Merge Sort | Heap Sort | Composite Sort |
|---|---:|---:|---:|---:|---:|
| 500 |  |  |  |  |  |
| 1000 |  |  |  |  |  |
| 2000 |  |  |  |  |  |
| 3000 |  |  |  |  |  |
| 4000 |  |  |  |  |  |
| 5000 |  |  |  |  |  |

---

## 9. Charts

### Worst-Case Runtime Chart

![Worst Case Runtime](charts/worst_case_chart.png)

### Average-Case Runtime Chart

![Average Case Runtime](charts/average_case_chart.png)

---

## 10. Conclusion

Based on the experimental results:

- Insertion Sort is suitable for small input sizes.
- Quick Sort performs well in many average-case situations.
- Merge Sort has stable `O(n log n)` performance.
- Heap Sort also has `O(n log n)` performance.
- Composite Sort can improve runtime by selecting a suitable sorting algorithm based on input size.

Final Composite Sort strategy:

```text
n <= _______: use __________________
n >  _______: use __________________
```

---

## Tested Runtime Results

The following results were produced by running the program in the testing environment used for this repository. Runtime unit: milliseconds.

### Worst-Case Runtime Results

| n | Insertion Sort | Quick Sort | Merge Sort | Heap Sort | Composite Sort |
|---:|---:|---:|---:|---:|---:|
| 500 | 0.050225 | 0.022920 | 0.011220 | 0.030225 | 0.019665 |
| 1000 | 0.194319 | 0.046449 | 0.022444 | 0.061539 | 0.046473 |
| 2000 | 0.760190 | 0.098457 | 0.047593 | 0.132262 | 0.102048 |
| 3000 | 1.741747 | 0.152379 | 0.088672 | 0.213064 | 0.155376 |
| 4000 | 3.005491 | 0.215054 | 0.107682 | 0.300559 | 0.241939 |
| 5000 | 4.713037 | 0.272737 | 0.126219 | 0.360478 | 0.270292 |

### Average-Case Runtime Results

| n | Insertion Sort | Quick Sort | Merge Sort | Heap Sort | Composite Sort |
|---:|---:|---:|---:|---:|---:|
| 500 | 0.029756 | 0.019443 | 0.022907 | 0.027657 | 0.020259 |
| 1000 | 0.105958 | 0.041981 | 0.054551 | 0.059232 | 0.043399 |
| 2000 | 0.399466 | 0.094680 | 0.110968 | 0.129027 | 0.092205 |
| 3000 | 0.862553 | 0.143264 | 0.170621 | 0.200064 | 0.145327 |
| 4000 | 1.523712 | 0.200158 | 0.233865 | 0.281654 | 0.198888 |
| 5000 | 2.321958 | 0.254527 | 0.303715 | 0.348907 | 0.258944 |

## Result Summary

Based on this test run:

- In the worst-case experiment, Merge Sort was the fastest algorithm for the tested input sizes from 500 to 5000.
- In the average-case experiment, Quick Sort was the fastest or nearly the fastest algorithm for the tested input sizes from 500 to 5000.
- Insertion Sort became much slower as n increased, which matches its O(n^2) behavior.
- Heap Sort had stable growth, but it was slower than Merge Sort in the worst-case experiment and slower than Quick Sort in the average-case experiment in this run.
- The current Composite Sort implementation uses Insertion Sort for n <= 32 and Quick Sort for larger n. This is suitable as a starting template, but the final thresholds should be adjusted according to the criterion required by the assignment.

Recommended Composite Sort strategies from this run:

```text
Worst-case criterion:
n <= 32: use Insertion Sort
n > 32:  use Merge Sort

Average-case criterion:
n <= 32: use Insertion Sort
n > 32:  use Quick Sort
```

Charts are stored in:

```text
charts/worst_case_chart.png
charts/average_case_chart.png
```

---

## 11. How to Compile and Run

### Compile with Makefile

```bash
make
```

### Run

```bash
./sorting_project
```

### Windows PowerShell without Makefile

```powershell
g++ -std=c++17 src/main.cpp src/sorting.cpp src/data_generator.cpp -o sorting_project.exe
./sorting_project.exe
```

### Generate Charts

```bash
cd scripts
python generate_charts.py
```

---

## 中文報告

中文版完整報告請見：

```text
report/sorting_project_report_zh.md
```

本報告包含：

1. 解題說明
2. 解題策略
3. 程式實作
4. 效能分析
5. 測試與驗證
6. 編譯與執行指令
7. 結論
8. 申論及開發報告
9. 雙人合作分工
10. Worst-case 與 Average-case 實測結果
