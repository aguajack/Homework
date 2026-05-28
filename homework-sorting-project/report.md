# 41343147

Homework Sorting Project

## 解題說明

本作業為排序法效能比較專題，主要目標是實作並測試多種排序法，觀察不同排序法在不同資料量與不同資料狀態下的執行效率。

本專題實作的排序法包含：

1. Insertion Sort
2. Quick Sort with Median-of-Three
3. Iterative Merge Sort
4. Heap Sort

除了完成四種排序法之外，本作業也需要設計一個 Composite Sort 函式。Composite Sort 的目標是根據輸入資料量大小，選擇較適合的排序法，以提升整體排序效率。

本專案測試的資料量為：

```text
n = 500, 1000, 2000, 3000, 4000, 5000
```

測試內容分成兩種：

1. Worst-case runtime 測試
2. Average-case runtime 測試

測試完成後，將結果輸出成 CSV 檔案，並繪製成圖表進行分析。

---

## 程式實作

本專案使用 C++ 實作，主要程式碼放在 `src/` 資料夾中。

專案結構如下：

```text
homework-sorting-project/
│
├── src/
│   ├── main.cpp
│   ├── sorting.cpp
│   ├── sorting.h
│   ├── data_generator.cpp
│   └── data_generator.h
│
├── data/
│   ├── average_case_results.csv
│   └── worst_case_results.csv
│
├── output/
│   ├── average_case_chart.png
│   └── worst_case_chart.png
│
├── Makefile
└── report.md
```

### 1. main.cpp

`main.cpp` 是主程式，負責執行以下工作：

1. 呼叫四種排序法。
2. 測試排序結果是否正確。
3. 執行 worst-case 測試。
4. 執行 average-case 測試。
5. 將測試結果輸出成 CSV 檔案。

### 2. sorting.h

`sorting.h` 是排序函式的標頭檔，負責宣告排序函式，例如：

```cpp
void insertionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int left, int right);
void iterativeMergeSort(std::vector<int>& arr);
void heapSort(std::vector<int>& arr);
void compositeSort(std::vector<int>& arr);
```

### 3. sorting.cpp

`sorting.cpp` 是排序法的實作檔，包含：

1. Insertion Sort
2. Quick Sort with Median-of-Three
3. Iterative Merge Sort
4. Heap Sort
5. Composite Sort
6. isSorted 檢查函式

### 4. data_generator.h 與 data_generator.cpp

這兩個檔案負責產生測試資料，包括：

1. 正向排序資料
2. 反向排序資料
3. 隨機排列資料
4. Merge Sort worst-case 測試資料

### 5. Composite Sort 設計

Composite Sort 的設計概念是根據資料量選擇排序法。

目前策略如下：

```cpp
void compositeSort(std::vector<int>& arr)
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
```

這個設計的原因是 Insertion Sort 在小資料量時成本較低，而 Quick Sort 在 average-case 中通常有良好的效能。

---

## 效能分析

### 1. 理論時間複雜度

| 排序法            |  Best Case | Average Case | Worst Case |
| -------------- | ---------: | -----------: | ---------: |
| Insertion Sort |       O(n) |       O(n^2) |     O(n^2) |
| Quick Sort     | O(n log n) |   O(n log n) |     O(n^2) |
| Merge Sort     | O(n log n) |   O(n log n) | O(n log n) |
| Heap Sort      | O(n log n) |   O(n log n) | O(n log n) |

### 2. 空間複雜度

| 排序法                  |    空間複雜度 | 說明          |
| -------------------- | -------: | ----------- |
| Insertion Sort       |     O(1) | 原地排序        |
| Quick Sort           | O(log n) | 平均情況下遞迴堆疊空間 |
| Iterative Merge Sort |     O(n) | 需要額外暫存陣列    |
| Heap Sort            |     O(1) | 原地排序        |

### 3. Worst-case 測試結果

測試結果存放於：

```text
data/worst_case_results.csv
```

圖表存放於：

```text
output/worst_case_chart.png
```

Worst-case 測試結果顯示，Insertion Sort 在資料量增加時執行時間成長明顯，符合 O(n^2) 的特性。Merge Sort 在 worst-case 中表現穩定，因為其理論 worst-case 時間複雜度為 O(n log n)。

### 4. Average-case 測試結果

測試結果存放於：

```text
data/average_case_results.csv
```

圖表存放於：

```text
output/average_case_chart.png
```

Average-case 測試使用隨機排列資料進行測試。測試結果顯示，Quick Sort 在隨機資料下通常有良好的效能，符合其 average-case O(n log n) 的特性。

### 5. Composite Sort 分析

Composite Sort 的目的不是只使用單一排序法，而是利用不同排序法在不同資料量下的優勢。

在小資料量時，Insertion Sort 的常數成本低，因此適合處理小型資料。

在較大資料量時，Quick Sort 在 average-case 中通常表現良好，因此目前 Composite Sort 選擇 Quick Sort 作為主要排序法。

如果專案更重視 worst-case 保證，也可以將大資料量時的排序法改為 Merge Sort。

---

## 測試與驗證

### 1. 測試環境

| 項目    | 內容                                 |
| ----- | ---------------------------------- |
| 程式語言  | C++                                |
| 編譯標準  | C++17                              |
| 編譯器   | g++                                |
| 最佳化參數 | -O2                                |
| 計時工具  | std::chrono::high_resolution_clock |
| 時間單位  | milliseconds                       |

### 2. 編譯方式

可使用以下指令編譯：

```bash
g++ -std=c++17 -O2 src/main.cpp src/sorting.cpp src/data_generator.cpp -o sorting_project
```

或使用 Makefile：

```bash
make
```

### 3. 執行方式

執行程式：

```bash
./sorting_project
```

成功執行後會看到：

```text
Correctness test passed.
All experiments completed.
```

### 4. 正確性測試

正式測速前，程式會先使用小型資料測試每個排序法是否能正確排序。

測試資料：

```text
5, 1, 4, 2, 3
```

正確結果：

```text
1, 2, 3, 4, 5
```

若所有排序法都能成功排序，程式會輸出：

```text
Correctness test passed.
```

### 5. Worst-case 測試方式

不同排序法的 worst-case 測試方式如下：

| 排序法            | 測試方式                            |
| -------------- | ------------------------------- |
| Insertion Sort | 使用反向排序資料                        |
| Quick Sort     | 使用多組隨機排列並取最大執行時間作為近似 worst-case |
| Merge Sort     | 使用自訂 worst-case 資料產生器           |
| Heap Sort      | 使用多組隨機排列並取最大執行時間作為近似 worst-case |

### 6. Average-case 測試方式

Average-case 測試使用隨機排列資料。

每個資料量會產生多組隨機資料，分別排序後計算平均執行時間。

### 7. 測試輸出檔案

測試完成後會產生：

```text
data/worst_case_results.csv
data/average_case_results.csv
```

圖表檔案為：

```text
output/worst_case_chart.png
output/average_case_chart.png
```

---

## 申論及開發報告

### 1. 開發流程

本專案開發流程如下：

1. 建立 C++ 專案架構。
2. 實作四種排序法。
3. 實作測試資料產生器。
4. 撰寫主程式進行測速。
5. 使用 CSV 儲存測試結果。
6. 產生圖表進行效能比較。
7. 根據測試結果設計 Composite Sort。
8. 整理報告並上傳至 GitHub。

### 2. 雙人合作分工

本專題採雙人合作方式完成，分工如下：

| 組員   | 負責內容      | 具體工作                            |
| ---- | --------- | ------------------------------- |
| 組員 A | 程式實作與測試整合 | 實作排序法、資料產生器、主程式與 Composite Sort |
| 組員 B | 實驗紀錄與報告整理 | 整理測試結果、製作圖表、撰寫分析與報告             |

### 3. 遇到的問題

本專案開發過程中遇到的主要問題包含：

1. 單次排序時間過短，不容易測量。
2. Quick Sort 與 Heap Sort 的 worst-case 不容易直接產生。
3. GitHub Actions 驗證器要求固定的 `report.md` 格式。
4. 專案資料夾需要整理成簡潔且符合繳交要求的結構。

### 4. 解決方式

對於上述問題，本專案採取以下解決方式：

1. 使用多組測試資料降低單次測量誤差。
2. Quick Sort 與 Heap Sort 使用多組隨機排列，取最大值近似 worst-case。
3. 將正式報告放在專案根目錄，檔名固定為 `report.md`。
4. 將專案整理為 `src/`、`data/`、`output/`、`Makefile` 與 `report.md` 的簡潔結構。

### 5. 結論

本專案完成了四種排序法的實作與效能比較。

根據測試結果可以觀察到：

1. Insertion Sort 適合小資料量。
2. Quick Sort 在 average-case 下表現良好。
3. Merge Sort 在 worst-case 下表現穩定。
4. Heap Sort 具有穩定的 O(n log n) 理論保證。
5. Composite Sort 可以根據資料量選擇較適合的排序法。

因此，Composite Sort 的設計可以結合不同排序法的優點，在不同情況下取得較好的排序效能。
