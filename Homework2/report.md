[README.md](https://github.com/user-attachments/files/27314153/README.md)

# 41343147

作業二

## 解題說明

本次作業根據 Graph 圖形資料結構章節，實作圖形的基本操作與常見演算法。Graph 是由頂點（Vertex）與邊（Edge）組成的資料結構，本作業使用 **Adjacency Matrix（鄰接矩陣）** 儲存圖，並實作以下演算法：

1. DFS（Depth First Search，深度優先搜尋）
2. BFS（Breadth First Search，廣度優先搜尋）
3. Connected Components（連通元件）
4. Dijkstra 最短路徑演算法

本次程式使用 **無向有權圖** 作為主要測試圖形，其中 DFS、BFS 與 Connected Components 只判斷頂點之間是否有邊，不使用權重大小；Dijkstra 則會使用邊的權重來計算從起點到其他頂點的最短距離。

### 圖形類型與演算法適用範圍

| 演算法 | 可用於有向圖 | 可用於無向圖 | 可用於有權圖 | 可用於無權圖 | 說明 |
|--------|--------------|--------------|--------------|--------------|------|
| DFS | 可以 | 可以 | 可以 | 可以 | 權重不影響走訪順序，只需要判斷邊是否存在。 |
| BFS | 可以 | 可以 | 可以 | 可以 | 在無權圖中也可用來找最短邊數路徑。 |
| Connected Components | 不適合直接使用 | 可以 | 可以 | 可以 | 本程式實作的是無向圖連通元件；有向圖通常要使用 Strongly Connected Components。 |
| Dijkstra | 可以 | 可以 | 需要非負權重 | 不建議作為主要用途 | 適合有權圖，且邊權重不可為負數。 |

### 解題策略

1. 使用二維矩陣 `matrix[i][j]` 表示頂點 `i` 到頂點 `j` 的邊權重。
2. 若兩點之間沒有邊，則使用 `INF` 表示無法直接到達。
3. DFS 使用遞迴方式，從起點一路往尚未拜訪過的相鄰頂點前進。
4. BFS 使用 Queue，先走訪距離起點較近的頂點，再逐層向外走訪。
5. Connected Components 透過多次 DFS 找出所有連通區塊。
6. Dijkstra 使用距離陣列 `distance[]`，反覆選擇目前距離最小且尚未確定的頂點，並更新相鄰頂點的最短距離。

Dijkstra 的核心更新公式為：

$$
\text{distance}[v] = \min(\text{distance}[v], \text{distance}[u] + w(u, v))
$$

其中：

- $u$：目前選到的最短距離頂點
- $v$：與 $u$ 相鄰的頂點
- $w(u, v)$：從 $u$ 到 $v$ 的邊權重

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

const int INF = 1000000000;

class Graph {
private:
    int vertexCount;
    bool directed;
    vector<vector<int>> matrix;

    void DFSUtil(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        for (int i = 0; i < vertexCount; i++) {
            if (matrix[vertex][i] != INF && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

public:
    Graph(int n, bool isDirected) {
        vertexCount = n;
        directed = isDirected;
        matrix.assign(vertexCount, vector<int>(vertexCount, INF));

        for (int i = 0; i < vertexCount; i++) {
            matrix[i][i] = 0;
        }
    }

    void addEdge(int from, int to, int weight) {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            cout << "Invalid edge: " << from << " -> " << to << endl;
            return;
        }

        if (weight < 0) {
            cout << "Dijkstra cannot use negative weight edges." << endl;
            return;
        }

        matrix[from][to] = weight;

        if (!directed) {
            matrix[to][from] = weight;
        }
    }

    void printMatrix() {
        cout << "Adjacency Matrix:" << endl;
        cout << setw(5) << " ";
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(5) << i;
        }
        cout << endl;

        for (int i = 0; i < vertexCount; i++) {
            cout << setw(5) << i;
            for (int j = 0; j < vertexCount; j++) {
                if (matrix[i][j] == INF) {
                    cout << setw(5) << "-";
                } else {
                    cout << setw(5) << matrix[i][j];
                }
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(vertexCount, false);

        cout << "DFS from " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(vertexCount, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS from " << start << ": ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << current << " ";

            for (int i = 0; i < vertexCount; i++) {
                if (matrix[current][i] != INF && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << endl;
    }

    void connectedComponents() {
        vector<bool> visited(vertexCount, false);
        int componentCount = 0;

        cout << "Connected Components:" << endl;

        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                DFSUtil(i, visited);
                cout << endl;
            }
        }
    }

    void dijkstra(int start) {
        vector<int> distance(vertexCount, INF);
        vector<bool> selected(vertexCount, false);

        distance[start] = 0;

        for (int count = 0; count < vertexCount; count++) {
            int u = -1;
            int minDistance = INF;

            for (int i = 0; i < vertexCount; i++) {
                if (!selected[i] && distance[i] < minDistance) {
                    minDistance = distance[i];
                    u = i;
                }
            }

            if (u == -1) {
                break;
            }

            selected[u] = true;

            for (int v = 0; v < vertexCount; v++) {
                if (!selected[v] && matrix[u][v] != INF && distance[u] + matrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + matrix[u][v];
                }
            }
        }

        cout << "Dijkstra shortest path from " << start << ":" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << "Vertex " << i << ": ";
            if (distance[i] == INF) {
                cout << "unreachable";
            } else {
                cout << distance[i];
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph(7, false);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    graph.printMatrix();
    cout << endl;

    graph.DFS(0);
    graph.BFS(0);
    cout << endl;

    graph.connectedComponents();
    cout << endl;

    graph.dijkstra(0);

    return 0;
}
```

## 效能分析

令圖中有 $V$ 個頂點、$E$ 條邊。

1. Adjacency Matrix 空間複雜度為 $O(V^2)$。
2. DFS 時間複雜度為 $O(V^2)$。因為本程式使用鄰接矩陣，每個頂點都需要掃描一整列矩陣。
3. BFS 時間複雜度為 $O(V^2)$。原因同樣是每次取出頂點後，都要掃描所有可能相鄰頂點。
4. Connected Components 時間複雜度為 $O(V^2)$。雖然可能多次呼叫 DFS，但每個頂點最後只會被拜訪一次，總掃描量仍與矩陣大小相關。
5. Dijkstra 時間複雜度為 $O(V^2)$。本程式未使用 Priority Queue，而是每次用線性搜尋找目前最小距離的頂點。
6. 額外空間複雜度為 $O(V)$，用於 `visited[]`、Queue、`distance[]` 與 `selected[]`。

## 測試與驗證

### 測試圖形

本程式建立 7 個頂點，編號為 $0$ 到 $6$。

邊與權重如下：

| 邊 | 權重 |
|----|------|
| 0 - 1 | 4 |
| 0 - 2 | 2 |
| 1 - 2 | 1 |
| 1 - 3 | 5 |
| 2 - 3 | 8 |
| 2 - 4 | 10 |
| 3 - 4 | 2 |
| 3 - 5 | 6 |
| 4 - 5 | 3 |

其中頂點 $6$ 沒有連接任何邊，作為孤立點，用來測試 Connected Components 與 Dijkstra 中不可到達的情況。

### 測試案例

| 測試案例 | 測試內容 | 預期結果 | 實際結果 |
|----------|----------|----------|----------|
| 測試一 | 從頂點 0 進行 DFS | 可以拜訪 0、1、2、3、4、5 | 符合預期 |
| 測試二 | 從頂點 0 進行 BFS | 可以逐層拜訪 0、1、2、3、4、5 | 符合預期 |
| 測試三 | 判斷 Connected Components | 分成兩個連通元件：0~5 與 6 | 符合預期 |
| 測試四 | 從頂點 0 執行 Dijkstra | 頂點 6 顯示 unreachable | 符合預期 |
| 測試五 | 檢查最短路徑 | 0 到 5 的最短距離為 13 | 符合預期 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o graph_homework main.cpp
$ ./graph_homework
```

Windows 環境可使用：

```shell
$ g++ -std=c++17 -o graph_homework.exe main.cpp
$ graph_homework.exe
```

### 執行結果

```text
Adjacency Matrix:
         0    1    2    3    4    5    6
    0    0    4    2    -    -    -    -
    1    4    0    1    5    -    -    -
    2    2    1    0    8   10    -    -
    3    -    5    8    0    2    6    -
    4    -    -   10    2    0    3    -
    5    -    -    -    6    3    0    -
    6    -    -    -    -    -    -    0

DFS from 0: 0 1 2 3 4 5 
BFS from 0: 0 1 2 3 4 5 

Connected Components:
Component 1: 0 1 2 3 4 5 
Component 2: 6 

Dijkstra shortest path from 0:
Vertex 0: 0
Vertex 1: 3
Vertex 2: 2
Vertex 3: 8
Vertex 4: 10
Vertex 5: 13
Vertex 6: unreachable
```

### 結論

1. 程式能正確使用 Adjacency Matrix 儲存無向有權圖。
2. DFS 能從起點一路往深處走訪所有可到達的頂點。
3. BFS 能從起點開始逐層走訪所有可到達的頂點。
4. Connected Components 能正確判斷圖中有兩個連通元件。
5. Dijkstra 能正確計算從頂點 0 到其他頂點的最短距離，並能判斷頂點 6 無法到達。

## 申論及開發報告

### 選擇 Adjacency Matrix 的原因

本程式使用 Adjacency Matrix 作為圖的儲存方式，主要原因如下：

1. **概念直觀**

   鄰接矩陣可以直接用 `matrix[i][j]` 表示頂點 $i$ 到頂點 $j$ 是否有邊。若有邊，矩陣中存放該邊的權重；若沒有邊，則使用 `INF` 表示不可直接到達。

2. **適合初學者理解圖的結構**

   相較於 Adjacency List，Adjacency Matrix 更容易看出頂點之間的連接關係，適合作為 Graph 基本操作的練習。

3. **方便實作 DFS、BFS 與 Dijkstra**

   DFS、BFS 與 Dijkstra 都需要尋找某個頂點的相鄰頂點。使用鄰接矩陣時，只要掃描該頂點對應的一整列，即可找出所有相鄰頂點。

### 選擇 DFS 的原因

DFS 是圖形走訪中最基本的演算法之一，適合用來理解圖中頂點的可達性。DFS 的核心概念是「先往深處走，走到底再回頭」。

在本程式中，DFS 使用遞迴實作，每次走到一個新頂點，就將該頂點標記為已拜訪，避免重複走訪或在圖中產生無限循環。

### 選擇 BFS 的原因

BFS 也是圖形走訪的重要演算法。與 DFS 不同，BFS 是一層一層向外走訪，因此適合用來觀察圖中頂點與起點之間的層級關係。

本程式使用 `queue<int>` 實作 BFS。當一個頂點被取出後，程式會檢查它所有尚未拜訪過的相鄰頂點，並將它們加入 Queue 中，等待後續處理。

### 選擇 Connected Components 的原因

Connected Components 可以用來判斷一張無向圖被分成幾個彼此不連通的區塊。這在圖論中是很重要的概念，例如可以用來分析網路是否全部連通。

本程式透過多次 DFS 完成 Connected Components 的判斷。若某個頂點尚未被拜訪，表示它不屬於前面已找到的連通元件，因此從該頂點重新執行 DFS，便可找出新的連通元件。

### 選擇 Dijkstra 的原因

Dijkstra 是常見的最短路徑演算法，適合用於邊權重非負的圖。因為本次程式使用有權圖，所以加入 Dijkstra 可以讓作業內容更完整，除了基本走訪之外，也能展示圖形演算法在路徑成本計算上的應用。

Dijkstra 的核心思想是每次選擇目前距離起點最近、且尚未確定最短距離的頂點，然後利用該頂點更新其他相鄰頂點的距離。

### 有向、無向、有權、無權的設計說明

本程式的 `Graph` 類別保留 `directed` 變數，因此可以透過建構子決定圖是有向圖或無向圖：

```cpp
Graph graph(7, false);
```

其中 `false` 代表無向圖。如果改成 `true`，則可以改為有向圖。

本次測試使用無向有權圖，原因是：

1. DFS 與 BFS 可以在無向圖中清楚展示走訪順序。
2. Connected Components 通常用於無向圖，較符合本次實作需求。
3. Dijkstra 需要使用權重，因此選擇有權圖作為測試資料。
4. 使用非負權重，符合 Dijkstra 演算法的限制。

### 兩人分工內容

| 成員 | 負責內容 |
|------|----------|
| 41343147 鄭亦閔| 負責 Graph 類別設計、Adjacency Matrix 建立、DFS、BFS、Connected Components 程式實作，以及主程式整合。 |
| 41343115 周子新| 負責 Dijkstra 最短路徑演算法、測試資料設計、執行結果確認、README 報告整理與 GitHub 專案排版。 |

### 開發過程遇到的問題與解決方式

1. **如何表示沒有邊的情況**

   一開始若使用 `0` 表示沒有邊，會和自己到自己的距離 `0` 混淆。因此本程式使用 `INF` 表示兩個不同頂點之間沒有直接連線。

2. **DFS 與 BFS 是否需要使用權重**

   DFS 與 BFS 的主要目的在於走訪頂點，因此只需要知道兩個頂點之間是否有邊，不需要使用邊的權重。程式中只判斷 `matrix[i][j] != INF`，代表有邊即可。

3. **Dijkstra 的限制**

   Dijkstra 無法處理負權重邊，因此在 `addEdge()` 中加入判斷，如果權重小於 0，就不加入該邊，避免演算法得到錯誤結果。

4. **孤立點的測試**

   為了確認 Connected Components 與 Dijkstra 是否能正確處理不可到達的頂點，本程式特別保留頂點 6 為孤立點。測試結果中，Connected Components 會將頂點 6 分成獨立的 Component，而 Dijkstra 會顯示 `unreachable`。

透過本次作業，可以理解 Graph 的基本表示方式與多種圖形演算法的差異。DFS 和 BFS 適合用來走訪圖，Connected Components 適合分析無向圖的連通區塊，而 Dijkstra 則適合用來計算有權圖中的最短路徑。
