# 41343147

# Homework Sorting Project 排序法效能比較報告

組員A:鄭亦閔
組員B:周子新

## 解題說明

本作業為排序法效能比較專題，主要目標是實作並測試多種排序法，觀察不同排序法在不同資料量與不同資料狀態下的執行效率。

本專題實作的排序法包含：

1. Insertion Sort
2. Quick Sort with Median-of-Three
3. Iterative Merge Sort
4. Heap Sort

除了完成四種排序法之外，本作業也設計一個 Composite Sort 函式。Composite Sort 的目標是根據輸入資料量大小，選擇較適合的排序法，以提升整體排序效率。

本專案測試的資料量為：

```text
n = 500, 1000, 2000, 3000, 4000, 5000
```

測試內容分成兩種：

1. Worst-case runtime 測試
2. Average-case runtime 測試

測試完成後，程式會將結果輸出成 CSV 檔案，並使用圖表輔助分析不同排序法的效能差異。

本作業最後的專案結構整理為：

```text
homework-sorting-project/
│
├── src/
├── data/
├── output/
├── Makefile
└── report.md
```

其中 `src/` 放置程式碼，`data/` 放置測試結果，`output/` 放置圖表，`report.md` 為本報告。

---

## 程式實作

本專案使用 C++ 實作，並將四種排序法分別寫在不同的 `.cpp` 檔案中，最後由 `main.cpp` 統一呼叫。這樣可以讓程式結構更清楚，也方便後續維護與測試。

專案中的程式碼主要放在 `src/` 資料夾中：

```text
src/
├── main.cpp
├── sorting.h
├── insertion_sort.cpp
├── quick_sort.cpp
├── merge_sort.cpp
├── heap_sort.cpp
├── composite_sort.cpp
├── data_generator.cpp
└── data_generator.h
```

### main.cpp

`main.cpp` 是主程式，負責執行整個測試流程。

主要工作包含：

1. 呼叫四種排序法。
2. 呼叫 Composite Sort。
3. 測試排序結果是否正確。
4. 執行 worst-case 測試。
5. 執行 average-case 測試。
6. 計算每種排序法的執行時間。
7. 將測試結果輸出成 CSV 檔案。

在本專案中，`main.cpp` 不直接實作排序演算法，而是透過 `sorting.h` 呼叫不同排序法。

### sorting.h

`sorting.h` 是排序函式的標頭檔，負責宣告所有排序函式，使其他 `.cpp` 檔案可以使用這些排序法。

主要宣告包含：

```cpp
void insertionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int left, int right);
void iterativeMergeSort(std::vector<int>& arr);
void heapSort(std::vector<int>& arr);
void compositeSort(std::vector<int>& arr);
bool isSorted(const std::vector<int>& arr);
```

### insertion_sort.cpp

`insertion_sort.cpp` 負責實作 Insertion Sort。

Insertion Sort 的核心想法是將每一個元素插入到前面已排序區間中的正確位置。

此排序法適合小資料量，因為程式結構簡單，常數成本低。但當資料量變大時，效率會明顯下降。

Insertion Sort 的 worst-case 通常發生在資料為反向排序時，例如：

```text
5, 4, 3, 2, 1
```

### quick_sort.cpp

`quick_sort.cpp` 負責實作 Quick Sort with Median-of-Three。

Quick Sort 會選擇一個 pivot，將資料分成比 pivot 小與比 pivot 大的兩部分，再分別遞迴排序。

本專案使用 Median-of-Three 方法選擇 pivot，也就是從 left、middle、right 三個位置中選出中位數作為 pivot，以降低選到極端 pivot 的機率。

### merge_sort.cpp

`merge_sort.cpp` 負責實作 Iterative Merge Sort。

本專案使用非遞迴版本的 Merge Sort，透過逐步合併小區間的方式完成排序。

Merge Sort 的優點是 worst-case、average-case 都具有穩定的 O(n log n) 時間複雜度。

### heap_sort.cpp

`heap_sort.cpp` 負責實作 Heap Sort。

Heap Sort 會先建立 max heap，再反覆將最大值移到陣列尾端，最後完成排序。

Heap Sort 的優點是 worst-case 仍然可以維持 O(n log n)，且可以原地排序。

### composite_sort.cpp

`composite_sort.cpp` 負責實作 Composite Sort。

Composite Sort 的設計概念是根據資料量大小選擇不同排序法。

目前設計方式如下：

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

此設計的原因是 Insertion Sort 在小資料量時成本較低，而 Quick Sort 在 average-case 中通常具有良好效能。

### data_generator.cpp 與 data_generator.h

`data_generator.cpp` 與 `data_generator.h` 負責產生測試資料。

產生的資料包含：

1. 正向排序資料
2. 反向排序資料
3. 隨機排列資料
4. Merge Sort worst-case 測試資料

這些資料會被 `main.cpp` 呼叫，用來測試不同排序法的執行時間。

---

## 效能分析

### 理論時間複雜度

| 排序法            |  Best Case | Average Case | Worst Case |
| -------------- | ---------: | -----------: | ---------: |
| Insertion Sort |       O(n) |       O(n^2) |     O(n^2) |
| Quick Sort     | O(n log n) |   O(n log n) |     O(n^2) |
| Merge Sort     | O(n log n) |   O(n log n) | O(n log n) |
| Heap Sort      | O(n log n) |   O(n log n) | O(n log n) |

### 空間複雜度

| 排序法                  |    空間複雜度 | 說明            |
| -------------------- | -------: | ------------- |
| Insertion Sort       |     O(1) | 原地排序          |
| Quick Sort           | O(log n) | 平均情況下需要遞迴堆疊空間 |
| Iterative Merge Sort |     O(n) | 需要額外暫存陣列      |
| Heap Sort            |     O(1) | 原地排序          |

### Worst-case 分析

Worst-case 測試結果存放於：

```text
data/worst_case_results.csv
```

Worst-case 圖表存放於：

```text
output/worst_case_chart.png
```

Insertion Sort 在反向排序資料下會產生大量搬移，因此執行時間會隨著資料量增加而快速上升，符合 O(n^2) 的特性。

Merge Sort 在 worst-case 下仍然具有 O(n log n) 的時間複雜度，因此表現較穩定。

Heap Sort 同樣具有 O(n log n) 的 worst-case 理論保證，但實際執行時間會受到 heapify 操作的常數成本影響。

Quick Sort 使用 Median-of-Three 可以降低選到極端 pivot 的機率，但理論上 worst-case 仍然可能退化為 O(n^2)。

### Average-case 分析

Average-case 測試結果存放於：

```text
data/average_case_results.csv
```

Average-case 圖表存放於：

```text
output/average_case_chart.png
```

Average-case 測試使用隨機排列資料進行測試。根據測試結果，Quick Sort 在隨機資料下通常表現良好，符合 average-case O(n log n) 的特性。

### Composite Sort 分析

Composite Sort 的目的，是將不同排序法的優點結合起來。

小資料量時使用 Insertion Sort，因為其實作簡單且常數成本較低。

大資料量時使用 Quick Sort，因為 Quick Sort 在 average-case 中通常有較好的實際執行效率。

如果更重視 worst-case 保證，也可以將大資料量時的排序法改為 Merge Sort。

---

## 測試與驗證

### 測試環境

| 項目    | 內容                                 |
| ----- | ---------------------------------- |
| 程式語言  | C++                                |
| 編譯標準  | C++17                              |
| 編譯器   | g++                                |
| 最佳化參數 | -O2                                |
| 計時工具  | std::chrono::high_resolution_clock |
| 時間單位  | milliseconds                       |

### 編譯方式

本專案可以使用 Makefile 編譯：

```bash
make
```

也可以直接使用 g++ 編譯：

```bash
g++ -std=c++17 -O2 src/main.cpp src/insertion_sort.cpp src/quick_sort.cpp src/merge_sort.cpp src/heap_sort.cpp src/composite_sort.cpp src/data_generator.cpp -o sorting_project
```

### 執行方式

執行程式：

```bash
./sorting_project
```

成功執行後，會看到：

```text
Correctness test passed.
All experiments completed.
```

### 正確性測試

在正式測速前，程式會先使用小型資料測試每個排序法是否能正確排序。

測試資料如下：

```text
5, 1, 4, 2, 3
```

正確排序結果應為：

```text
1, 2, 3, 4, 5
```

若所有排序法皆能正確排序，程式會輸出：

```text
Correctness test passed.
```

### Worst-case 測試方式

不同排序法的 worst-case 測試方式如下：

| 排序法            | 測試方式                            |
| -------------- | ------------------------------- |
| Insertion Sort | 使用反向排序資料                        |
| Quick Sort     | 使用多組隨機排列並取最大執行時間作為近似 worst-case |
| Merge Sort     | 使用自訂 worst-case 資料產生器           |
| Heap Sort      | 使用多組隨機排列並取最大執行時間作為近似 worst-case |

### Average-case 測試方式

Average-case 測試使用隨機排列資料。

每個資料量會產生多組隨機資料，分別排序後計算平均執行時間。

### 測試輸出檔案

測試完成後會產生以下 CSV 檔案：

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

### 開發流程

本專案開發流程如下：

1. 建立 C++ 專案架構。
2. 實作四種排序法。
3. 將四種排序法拆分成不同 `.cpp` 檔案。
4. 實作測試資料產生器。
5. 撰寫主程式進行測速。
6. 使用 CSV 儲存測試結果。
7. 產生圖表進行效能比較。
8. 根據測試結果設計 Composite Sort。
9. 整理報告並上傳至 GitHub。

### 雙人合作分工

本專題採雙人合作方式完成，分工如下：

| 組員   | 負責內容      | 具體工作                            |
| ---- | --------- | ------------------------------- |
| 組員 A | 程式實作與測試整合 | 實作排序法、資料產生器、主程式與 Composite Sort |
| 組員 B | 實驗紀錄與報告整理 | 整理測試結果、製作圖表、撰寫分析與報告             |

### 遇到的問題

本專案開發過程中遇到的主要問題包含：

1. 單次排序時間過短，不容易測量。
2. Quick Sort 與 Heap Sort 的 worst-case 不容易直接產生。
3. GitHub Actions 驗證器要求固定的 `report.md` 格式。
4. 專案資料夾需要整理成簡潔且符合繳交要求的結構。
5. 原本排序法集中在同一個檔案中，程式結構較不清楚。

### 解決方式

對於上述問題，本專案採取以下解決方式：

1. 使用多組測試資料降低單次測量誤差。
2. Quick Sort 與 Heap Sort 使用多組隨機排列，取最大值近似 worst-case。
3. 將正式報告放在專案根目錄，檔名固定為 `report.md`。
4. 將專案整理為 `src/`、`data/`、`output/`、`Makefile` 與 `report.md` 的簡潔結構。
5. 將四種排序法拆分成不同 `.cpp` 檔案，再由 `main.cpp` 統一呼叫。

### 結論

本專案完成了四種排序法的實作與效能比較。

根據測試結果可以觀察到：

1. Insertion Sort 適合小資料量。
2. Quick Sort 在 average-case 下表現良好。
3. Merge Sort 在 worst-case 下表現穩定。
4. Heap Sort 具有穩定的 O(n log n) 理論保證。
5. Composite Sort 可以根據資料量選擇較適合的排序法。

因此，Composite Sort 的設計可以結合不同排序法的優點，在不同情況下取得較好的排序效能。
