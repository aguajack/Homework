
# 41343147

# 作業一 Max/Min Heap

## 解題說明

本題要求先撰寫一個 C++ 抽象類別 MinPQ，用來表示 Min Priority Queue，再撰寫一個 MinHeap 類別繼承自 MinPQ，並實作其中所有虛擬函式

Min Priority Queue 的核心概念如下：

每次取出的元素為目前集合中的最小值
必須支援插入元素、取得最小元素、刪除最小元素等操作

在本題中，我使用 Binary Heap 來實作 Min Priority Queue。
由於 Min Heap 具有以下性質：

父節點的值必須小於等於子節點的值

因此整棵 heap 中的最小元素會固定出現在根節點，這樣就可以有效率地完成 Top()、Push() 與 Pop() 等操作。

### 解題策略

1. 先建立抽象類別 MinPQ，定義四個基本操作：
IsEmpty()
Top()
Push(const T&)
Pop()
再建立 MinHeap 類別繼承 MinPQ，並使用 vector 作為底層儲存結構。
採用 1-based index 來表示 binary heap，方便計算父節點與子節點位置：
父節點：i / 2
左子節點：2 * i
右子節點：2 * i + 1
插入元素時，先將元素放到最後，再透過 Bubble Up 向上調整。
刪除最小元素時，先將最後一個元素放到根節點，再透過 Bubble Down 向下調整。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap;   // 使用 1-based index，heap[0] 不使用

    void BubbleUp(int index) {
        while (index > 1) {
            int parent = index / 2;
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void BubbleDown(int index) {
        int n = (int)heap.size() - 1;

        while (index * 2 <= n) {
            int left = index * 2;
            int right = left + 1;
            int smaller = left;

            if (right <= n && heap[right] < heap[left]) {
                smaller = right;
            }

            if (heap[smaller] < heap[index]) {
                swap(heap[smaller], heap[index]);
                index = smaller;
            } else {
                break;
            }
        }
    }

public:
    MinHeap() {
        heap.push_back(T());
    }

    bool IsEmpty() const override {
        return heap.size() == 1;
    }

    const T& Top() const override {
        if (IsEmpty()) {
            throw runtime_error("MinHeap is empty");
        }
        return heap[1];
    }

    void Push(const T& x) override {
        heap.push_back(x);
        BubbleUp((int)heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) {
            throw runtime_error("MinHeap is empty");
        }

        int last = (int)heap.size() - 1;
        heap[1] = heap[last];
        heap.pop_back();

        if (!IsEmpty()) {
            BubbleDown(1);
        }
    }
};

int main() {
    MinHeap<int> h;

    h.Push(40);
    h.Push(20);
    h.Push(50);
    h.Push(10);
    h.Push(30);

    cout << h.Top() << endl;   // 10
    h.Pop();
    cout << h.Top() << endl;   // 20

    return 0;
}

```

## 效能分析

1.時間複雜度

時間複雜度

Min Heap 的各項操作時間複雜度如下：

IsEmpty()：只需檢查目前 heap 是否為空，時間複雜度為 O(1)
Top()：直接回傳根節點，時間複雜度為 O(1)
Push()：最壞情況下新元素要一路上浮到根節點，因此時間複雜度為 O(log n)
Pop()：最壞情況下根節點替換後要一路下沉到葉節點，因此時間複雜度為 O(log n)
| 函式          | 功能     |    時間複雜度   |
| :---------- | :----- | :--------: |
| `IsEmpty()` | 判斷是否為空 |   `O(1)`   |
| `Top()`     | 取得最小元素 |   `O(1)`   |
| `Push()`    | 插入元素   | `O(log n)` |
| `Pop()`     | 刪除最小元素 | `O(log n)` |


2.空間複雜度

本程式使用 vector<T> 儲存 heap 中所有元素，因此若共有 n 個元素，所需儲存空間與元素個數成正比。

因此空間複雜度為：O(n)

其中：

heap 本體需要儲存所有節點
BubbleUp() 與 BubbleDown() 僅使用少量額外變數
不需要額外建立與 n 同階的輔助陣列

## 測試與驗證

### 測試案例

| 測試案例 | 操作                                  |  預期輸出  |  實際輸出  |
| :--: | :---------------------------------- | :----: | :----: |
|  測試一 | 插入 `40, 20, 50, 10, 30` 後執行 `Top()` |  `10`  |  `10`  |
|  測試二 | 上述資料再執行一次 `Pop()` 後 `Top()`         |  `20`  |  `20`  |
|  測試三 | 空 heap 執行 `IsEmpty()`               | `true` | `true` |
|  測試四 | 插入單一元素 `5` 後執行 `Top()`              |   `5`  |   `5`  |
|  測試五 | 連續插入多筆資料後檢查是否維持 Min Heap 性質         |   正確   |   正確   |



### 編譯與執行指令
```shell
$ g++ Problem1.cpp -std=c++14 -o Problem1
$ Problem1.exe
10
```

### 結論

本題透過抽象類別 MinPQ 定義了 Min Priority Queue 的基本介面，並使用 MinHeap 完成具體實作。
在實作過程中，我利用 Min Heap 的結構特性，讓最小值永遠維持在根節點，因此能夠快速完成 Top() 操作。
對於插入與刪除操作，則分別透過 Bubble Up 與 Bubble Down 維持 heap 性質，使 Push() 與 Pop() 的時間複雜度都保持在 O(log n)。
本題讓我更清楚理解：
抽象類別如何定義資料結構介面
heap 如何透過陣列表示完全二元樹
為什麼 heap 能有效率地實作 priority queue

# 作業二 Binary Search Tree
   
## 解題說明

本題分成兩個部分。

第一部分要求從空的 Binary Search Tree（BST）開始，對不同的 n 進行隨機插入，量測樹高 height，再計算比值

並觀察當 n = 100, 500, 1000, 2000, 3000, \dots, 10000 時，這個比值是否大致維持在常數附近。第二部分則要求撰寫一個 C++ 函式，刪除 BST 中 key 為 k 的節點，並分析其時間複雜度。

在本題中，我使用 Binary Search Tree 的基本性質來完成實作：

若插入值小於目前節點，則往左子樹插入
若插入值大於目前節點，則往右子樹插入

因此 BST 可以維持「左小右大」的結構。
而樹高的定義則為：

空樹高度為 0
非空樹高度為 1 + max(leftHeight, rightHeight)

透過這個定義，就可以在建立完成 BST 後計算其高度，並進一步求出題目要求的比值。

## 解題策略
   先建立一棵空的 BST。
對每個指定的 n，隨機產生 n 個不重複整數。
將這些數字依序插入 BST。
以遞迴方式計算樹高 height。
再計算比值，輸出各組 n 的結果，觀察比值是否接近常數。

第二部分：刪除 BST 中 key = k 的節點

刪除 BST 節點時分成三種情況：

該節點沒有子節點
直接刪除即可。
該節點只有一個子節點
用它的子節點取代原本的位置。
該節點有兩個子節點
找出右子樹中的最小節點（inorder successor），用該值取代目前節點，再遞迴刪除右子樹中的 successor。


   
## 程式實作
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
using namespace std;

class BST {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* Insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = Insert(node->left, key);
        } else if (key > node->key) {
            node->right = Insert(node->right, key);
        }

        return node;
    }

    int Height(Node* node) const {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = Height(node->left);
        int rightHeight = Height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    Node* FindMin(Node* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* Delete(Node* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = Delete(node->left, key);
        } else if (key > node->key) {
            node->right = Delete(node->right, key);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = FindMin(node->right);
            node->key = temp->key;
            node->right = Delete(node->right, temp->key);
        }

        return node;
    }

    void Inorder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        Inorder(node->left);
        cout << node->key << " ";
        Inorder(node->right);
    }

    void Clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        Clear(node->left);
        Clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        Clear(root);
    }

    void Insert(int key) {
        root = Insert(root, key);
    }

    int Height() const {
        return Height(root);
    }

    void Delete(int key) {
        root = Delete(root, key);
    }

    void PrintInorder() const {
        Inorder(root);
        cout << endl;
    }
};

vector<int> GenerateRandomData(int n) {
    vector<int> data;
    unordered_set<int> used;

    while ((int)data.size() < n) {
        int x = rand();
        if (used.find(x) == used.end()) {
            used.insert(x);
            data.push_back(x);
        }
    }

    return data;
}

double TestBSTHeightRatio(const vector<int>& data) {
    BST tree;

    for (int i = 0; i < (int)data.size(); ++i) {
        tree.Insert(data[i]);
    }

    int h = tree.Height();
    int n = (int)data.size();

    return (double)h / log2((double)n);
}

int main() {
    srand((unsigned)time(0));

    vector<int> testN = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    cout << "n\tHeight/log2(n)" << endl;
    for (int i = 0; i < (int)testN.size(); ++i) {
        vector<int> data = GenerateRandomData(testN[i]);
        double ratio = TestBSTHeightRatio(data);
        cout << testN[i] << "\t" << ratio << endl;
    }

    cout << endl;
    cout << "Delete test:" << endl;

    BST tree;
    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(20);
    tree.Insert(40);
    tree.Insert(60);
    tree.Insert(80);

    cout << "Before delete: ";
    tree.PrintInorder();

    tree.Delete(50);

    cout << "After delete 50: ";
    tree.PrintInorder();

    return 0;
}

```

## 效能分析

1. **時間複雜度（Time Complexity）**

(1) 插入 Insert
BST 的插入操作會從根節點開始比較，並沿著某一條路徑往下走，直到找到空位置為止。
因此插入所需時間與樹高 h 成正比。
```
Insert = O(h)
```
若樹形平衡，則 h ≈ log n，此時為：
```
O(log n)
```
若 BST 退化成鏈結串列，則最壞情況為：
```
O(n)
```
(2) 計算高度 Height
計算樹高時，必須拜訪每一個節點一次，因此若共有 n 個節點，整體時間複雜度為：
```
O(n)
```
(3) 刪除 Delete
刪除節點前，必須先找到該節點；找到後若有兩個子節點，還需到右子樹找最小值節點。
這些操作都只會沿著樹高方向進行，因此刪除的時間複雜度為：
```
O(h)
```
也就是：
平均情況：O(log n)
最壞情況：O(n)
(4) 高度比值實驗
對一組大小為 n 的資料：
建立 BST 需要進行 n 次插入每次插入平均約為 O(log n)因此平均情況下建樹成本可估計為：
```
O(n log n)
```
之後再做一次高度計算：
```
O(n)
```
所以單次測試大致為：
```
O(n log n) 
```
2. **空間複雜度（Space Complexity）**

   BST 需為每個節點配置一個 Node，共儲存 n 個節點，因此主體空間複雜度為：
```
O(n)
```
此外：
Height() 為遞迴函式，呼叫堆疊深度為 O(h)
Delete() 也是遞迴函式，呼叫堆疊深度同樣為 O(h)
因此整體空間複雜度可寫為：
 | 項目       |  空間複雜度 |
| :------- | :----: |
| BST 節點儲存 | `O(n)` |
| 遞迴堆疊     | `O(h)` |
| 總體主要空間   | `O(n)` |

   ## 測試與驗證
   
   ### 測試案例
(1) 高度比值測試
| 測試案例 | 節點數 `n` | 觀察項目                  |
| :--: | :-----: | :-------------------- |
|  測試一 |  `100`  | 計算 `height / log2(n)` |
|  測試二 |  `500`  | 計算 `height / log2(n)` |
|  測試三 |  `1000` | 計算 `height / log2(n)` |
|  測試四 |  `5000` | 計算 `height / log2(n)` |
|  測試五 | `10000` | 計算 `height / log2(n)` |

(2) 刪除操作測試
以下節點建立 BST：
```
50, 30, 70, 20, 40, 60, 80
```
其中中序走訪結果應為：
```
20 30 40 50 60 70 80
```
當刪除 50 時，由於 50 同時具有左、右子樹，因此需找右子樹最小值 60 取代，再刪除原本的 60 節點。刪除後中序走訪結果應為：
```
20 30 40 60 70 80
```
### 編譯與執行指令
```shell
$ g++ Problem2.cpp -std=c++14 -o Problem2
$ Problem2.exe
```
## 結論
本題第一部分透過隨機資料建立 BST，並量測樹高與 log_2 n 的比值。從理論上來看，隨機 BST 的高度通常與 log n 同階，因此這個比值應該接近常數。
第二部分實作了 BST 的刪除函式，並完整處理三種情況：
無子節點
單一子節點
兩個子節點
經由本題可以更清楚理解：
BST 的插入與搜尋是如何依照左小右大的規則進行
樹高會直接影響插入、搜尋與刪除效率
刪除節點時，兩子節點情況的處理方式是以 inorder successor 取代
本題也顯示出 BST 的效率與樹形高度密切相關。若輸入資料接近隨機，平均情況通常良好；但若輸入順序不佳，BST 可能退化，導致操作效率下降。
## 申論及開發報告

### 選擇 Binary Search Tree 的原因

在這題中，我使用 Binary Search Tree 來完成插入、刪除與高度分析，主要原因如下：

結構規則清楚
BST 的左子樹小於根節點、右子樹大於根節點，這樣的規則使搜尋、插入與刪除都有明確方向。
便於分析樹高與效率關係
題目要求觀察 height / log2(n) 的變化，因此使用 BST 可以直接研究資料分布與樹高之間的關係。
刪除操作具有代表性
BST 的刪除包含三種典型情況，是樹狀資料結構中很重要的基本操作。
## 實作心得

在實作這題時，我認為最重要的部分有兩個：

第一是隨機資料的建立，必須避免重複值，否則會影響 BST 節點數量。
第二是刪除函式的兩子節點情況，必須先找 successor，再遞迴刪除 successor，才能保持 BST 結構正確。
透過這次作業，我對 BST 的基本操作、樹高意義，以及平均與最壞情況的差異，都有更完整的理解。
