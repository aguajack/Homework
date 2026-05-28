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
