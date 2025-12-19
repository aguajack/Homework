# 41343147

作業三

## 解題說明

設計一個能表示並操作**一元多項式**的程式。  
每個多項式由若干項 `(係數, 次方)` 組成，例如：

- A(x) = 4x^5 - 2x^3 + 7
- B(x) = x^4 + 3

相加後：

- C(x) = A(x) + B(x) = 4x^5 + x^4 - 2x^3 + 10

---

### 想法（How to do?）

1. 建立 `Term` 結構來儲存每一項的係數與次方。  
2. 建立單向鏈結串列 `Chain<Term>` 來存所有項目，並維持 `exp` 遞減排序。  
3. 建立 `ChainIterator` 支援 `++it`、`it->exp`、`it->coef` 走訪。  
4. 設計 `newTerm(coef, exp)`：插入、合併同次方、係數為 0 刪除節點。  
5. `operator+` 用 merge 合併兩條已排序串列。  
6. `operator-` 將另一多項式係數取負後用加法完成。  
7. `operator*` 雙層迴圈相乘，結果交給 `newTerm` 合併同次方。  
8. 加分：用 `AvailableList`（free list）回收與重用節點，降低 new/delete 次數。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

template <class T> class Chain;
template <class T> class ChainIterator;
template <class T> class AvailableList;

template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    T element;
    ChainNode<T>* next;
public:
    ChainNode() : next(nullptr) {}
    ChainNode(const T& elem) : element(elem), next(nullptr) {}
    ChainNode(const T& elem, ChainNode<T>* nextNode) : element(elem), next(nextNode) {}
    void setElement(const T& elem) { element = elem; }
    void setNext(ChainNode<T>* nextNode) { next = nextNode; }
};

template <class T>
class AvailableList {
private:
    static ChainNode<T>* available;
public:
    static ChainNode<T>* getNode() {
        if (!available) return nullptr;
        ChainNode<T>* p = available;
        available = available->next;
        p->next = nullptr;
        return p;
    }

    static void getBack(ChainNode<T>* p) {
        if (!p) return;
        ChainNode<T>* tail = p;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = available;
        available = p;
    }

    static void clearAll() {
        while (available) {
            ChainNode<T>* nxt = available->next;
            delete available;
            available = nxt;
        }
    }
};

template <class T>
ChainNode<T>* AvailableList<T>::available = nullptr;

template <class T>
class ChainIterator {
private:
    ChainNode<T>* current;
public:
    ChainIterator(ChainNode<T>* start = nullptr) : current(start) {}

    T& operator*() const { return current->element; }
    T* operator->() const { return &(current->element); }

    ChainIterator<T>& operator++() {
        if (current) current = current->next;
        return *this;
    }

    ChainIterator<T> operator++(int) {
        ChainIterator<T> tmp(*this);
        ++(*this);
        return tmp;
    }

    bool operator==(const ChainIterator<T>& rhs) const { return current == rhs.current; }
    bool operator!=(const ChainIterator<T>& rhs) const { return current != rhs.current; }

    int operator-(const ChainIterator<T>& rhs) const {
        int idx = 0;
        ChainNode<T>* p = rhs.current;
        while (p && p != current) {
            p = p->next;
            ++idx;
        }
        return idx;
    }

    friend class Chain<T>;
};

template <class T>
class Chain {
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    ChainNode<T>* head;
public:
    Chain() : head(nullptr) {}

    ~Chain() {
        ChainNode<T>* current = head;
        while (current != nullptr) {
            ChainNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    ChainIterator<T> begin() const { return ChainIterator<T>(head); }
    ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }

    ChainNode<T>* release() {
        ChainNode<T>* p = head;
        head = nullptr;
        return p;
    }

    int size() const {
        int n = 0;
        for (ChainNode<T>* p = head; p != nullptr; p = p->next) ++n;
        return n;
    }

    void insert(int idx, const T& element) {
        ChainNode<T>* newNode = AvailableList<T>::getNode();
        if (!newNode) {
            newNode = new ChainNode<T>(element);
        } else {
            newNode->setElement(element);
        }

        if (idx == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            ChainNode<T>* prev = head;
            for (int i = 0; i < idx - 1 && prev != nullptr; ++i) {
                prev = prev->next;
            }
            if (prev != nullptr) {
                newNode->next = prev->next;
                prev->next = newNode;
            } else {
                AvailableList<T>::getBack(newNode);
            }
        }
    }

    bool erase(int idx) {
        if (idx < 0 || head == nullptr) return false;

        if (idx == 0) {
            ChainNode<T>* del = head;
            head = head->next;
            del->next = nullptr;
            AvailableList<T>::getBack(del);
            return true;
        }

        ChainNode<T>* prev = head;
        for (int i = 0; i < idx - 1 && prev != nullptr; ++i) prev = prev->next;
        if (prev == nullptr || prev->next == nullptr) return false;

        ChainNode<T>* del = prev->next;
        prev->next = del->next;
        del->next = nullptr;
        AvailableList<T>::getBack(del);
        return true;
    }
};

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
public:
    struct Term {
        double coef;
        int exp;
        Term(double c = 0, int e = 0) : coef(c), exp(e) {}
    };

private:
    Chain<Term> terms;

public:
    Polynomial() {}

    Polynomial(const Polynomial& other) {
        for (ChainIterator<Term> it = other.begin(); it != other.end(); ++it) {
            terms.insert(it - other.begin(), *it);
        }
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            AvailableList<Term>::getBack(terms.release());
            for (ChainIterator<Term> it = other.begin(); it != other.end(); ++it) {
                terms.insert(it - other.begin(), *it);
            }
        }
        return *this;
    }

    ~Polynomial() {
        AvailableList<Term>::getBack(terms.release());
    }

    ChainIterator<Term> begin() const { return terms.begin(); }
    ChainIterator<Term> end() const { return terms.end(); }

    void newTerm(double coef, int exp) {
        if (coef == 0) return;

        int index = 0;
        for (ChainIterator<Term> it = terms.begin(); it != terms.end(); ++it, ++index) {
            if (it->exp < exp) {
                break;
            } else if (it->exp == exp) {
                it->coef += coef;
                if (it->coef == 0) terms.erase(index);
                return;
            }
        }
        terms.insert(index, Term(coef, exp));
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        ChainIterator<Term> it1 = this->begin();
        ChainIterator<Term> it2 = other.begin();

        while (it1 != this->end() && it2 != other.end()) {
            if (it1->exp > it2->exp) {
                result.newTerm(it1->coef, it1->exp);
                ++it1;
            } else if (it1->exp < it2->exp) {
                result.newTerm(it2->coef, it2->exp);
                ++it2;
            } else {
                double newCoef = it1->coef + it2->coef;
                if (newCoef != 0) result.newTerm(newCoef, it1->exp);
                ++it1;
                ++it2;
            }
        }

        while (it1 != this->end()) {
            result.newTerm(it1->coef, it1->exp);
            ++it1;
        }

        while (it2 != other.end()) {
            result.newTerm(it2->coef, it2->exp);
            ++it2;
        }

        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial negOther;
        for (ChainIterator<Term> it = other.begin(); it != other.end(); ++it) {
            negOther.newTerm(-it->coef, it->exp);
        }
        return (*this) + negOther;
    }

    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        for (ChainIterator<Term> it1 = this->begin(); it1 != this->end(); ++it1) {
            for (ChainIterator<Term> it2 = other.begin(); it2 != other.end(); ++it2) {
                double newCoef = it1->coef * it2->coef;
                int newExp = it1->exp + it2->exp;
                result.newTerm(newCoef, newExp);
            }
        }
        return result;
    }

    float Evaluate(float x) const {
        long double sum = 0.0L;
        for (ChainIterator<Term> it = begin(); it != end(); ++it) {
            sum += (long double)it->coef * pow((long double)x, (long double)it->exp);
        }
        return (float)sum;
    }
};

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    int n;
    if (!(is >> n)) return is;

    AvailableList<Polynomial::Term>::getBack(poly.terms.release());

    for (int i = 0; i < n; ++i) {
        double c;
        int e;
        is >> c >> e;
        poly.newTerm(c, e);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    int n = poly.terms.size();
    os << n;
    for (ChainIterator<Polynomial::Term> it = poly.begin(); it != poly.end(); ++it) {
        os << " " << it->coef << " " << it->exp;
    }
    return os;
}

int main() {
    Polynomial A, B;
    cout << "Input A: ";
    cin >> A;
    cout << "Input B: ";
    cin >> B;

    cout << "A = " << A << "\n";
    cout << "B = " << B << "\n";
    cout << "A+B = " << (A + B) << "\n";
    cout << "A-B = " << (A - B) << "\n";
    cout << "A*B = " << (A * B) << "\n";

    float x;
    cout << "x = ";
    cin >> x;
    cout << "A(x) = " << A.Evaluate(x) << "\n";

    AvailableList<Polynomial::Term>::clearAll();
    return 0;
}

```

## 效能分析

假設：
- 多項式 A 有 `m` 項
- 多項式 B 有 `n` 項

---

## 時間複雜度（Time Complexity）

這份程式在做加法時（`operator+`）確實是用兩個迭代器一路比到結尾，所以「比對 A、B 的項」這段本來看起來像 `O(m+n)`。:contentReference[oaicite:0]{index=0}  

但重點是：**每次要把一項加到結果多項式 `result` 時，不是直接放進去**，而是呼叫 `result.newTerm(...)`。:contentReference[oaicite:1]{index=1}  
`newTerm` 會從結果串列的開頭開始找「應該插哪裡」（或找同次方來合併），等於每加一項可能都要掃過目前結果裡的很多項。:contentReference[oaicite:2]{index=2}  
如果真的需要插入新節點，`Chain::insert` 也會再走訪一次到指定位置。:contentReference[oaicite:3]{index=3}  

所以最壞情況下（幾乎每項都要插入、又常常要掃到很後面），就會變成：
- 第 1 次加進 result：掃 1 個
- 第 2 次：掃 2 個
- ...
- 第 (m+n) 次：掃 (m+n) 個

加起來大概就是 `1 + 2 + ... + (m+n)`，所以：

> **最壞時間複雜度：`O((m+n)^2)`**

---

## 空間複雜度（Space Complexity）

這份程式用鏈結串列存多項式。:contentReference[oaicite:4]{index=4}  
做 `A + B` 時會另外建一個 `result`，最多可能存到 `m+n` 項（最極端情況每項都不同次方）。:contentReference[oaicite:5]{index=5}  

> **空間複雜度：`O(m+n)`**

補充：`AvailableList` 只是把刪掉的節點先回收起來下次重用，主要是減少 `new/delete`，但不會改變上面的大 O。:contentReference[oaicite:6]{index=6}



## 測試與驗證

> 本程式的輸入格式：先輸入項數 `n`，再輸入 `n` 組 `(coef exp)`。  
> 輸出格式：`n coef exp coef exp ...`（空多項式輸出 `0`）。:contentReference[oaicite:0]{index=0}

---

## 測試案例（加法 A+B）

| 測試編號 | 測試目的 | 輸入資料（數學表示） | 實際輸入（程式格式） | 預期輸出（A+B） | 實際輸出（A+B） | 結果 |
|:--:|:--|:--|:--|:--|:--|:--:|
| 1 | 基本加法 + 常數抵消 | A = 2X² + 3X + 4<br>B = 5X − 4 | A: `3 2 2 3 1 4 0`<br>B: `2 5 1 -4 0` | `2 2 2 8 1` | `2 2 2 8 1` | ✅ |
| 2 | 次方完全不重疊 | A = X⁴ + 2X²<br>B = 3X³ + 4X | A: `2 1 4 2 2`<br>B: `2 3 3 4 1` | `4 1 4 3 3 2 2 4 1` | `4 1 4 3 3 2 2 4 1` | ✅ |
| 3 | 項目互相抵消變 0 | A = 5X³ − 2X<br>B = −5X³ + 2X | A: `2 5 3 -2 1`<br>B: `2 -5 3 2 1` | `0` | `0` | ✅ |
| 4 | 長度不同（其中一邊先結束） | A = 4X³ + 2X² + 1<br>B = 3X² + 5X | A: `3 4 3 2 2 1 0`<br>B: `2 3 2 5 1` | `4 4 3 5 2 5 1 1 0` | `4 4 3 5 2 5 1 1 0` | ✅ |
| 5 | 0 多項式輸入 | A = 0<br>B = 3X + 1 | A: `0`<br>B: `2 3 1 1 0` | `2 3 1 1 0` | `2 3 1 1 0` | ✅ |

---

## 效能量測（以本程式碼的實作方式為準）

### 分析結果

- **執行時間不會是線性 `O(m+n)`**  
  雖然加法在「比對兩邊項目」時是線性走訪，但每次把項目加進結果都會呼叫 `newTerm`，而 `newTerm` 會從結果串列開頭一路掃描找插入位置；需要插入時 `insert` 也會再走訪一次。  
  所以整體在項數變大時，常見現象是 **成長速度明顯快於線性**，最壞情況接近 **`O((m+n)^2)`**。

- **沒有「動態陣列倍增」這件事**  
  這份程式不是用 `termArray` 或倍增策略，而是用 **鏈結串列（Chain）** 存項目；插入成本主要來自「走訪找位置」，不是擴充陣列。  

- **記憶體使用量會隨結果項數增加，且回收機制降低配置成本**  
  加法會建立 `result`，最多可能需要約 `m+n` 個節點空間；同時程式用 `AvailableList` 回收已釋放節點，下次可重用，通常能減少 `new/delete` 次數、讓配置更穩定。  
  只要程式最後有呼叫 `clearAll()`，回收串列也會被清掉，避免一直累積。

> **結論：**  
> 本程式的多項式加法在資料量變大時，時間通常會比線性更慢（最壞接近平方級），但節點回收機制能讓記憶體配置行為更穩定、降低反覆配置的成本；整體屬於「功能正確、但大規模資料效能受 `newTerm` 線性掃描影響」的實作。

## 申論及開發報告

這次作業讓我更清楚體會到 **物件導向設計** 與 **動態記憶體管理** 在 C++ 開發中的重要性。這份程式以 `Polynomial` 類別為核心，內部用鏈結串列 `Chain<Term>` 儲存每一項（係數與次方），並透過運算子多載完成多項式的加、減、乘與代入計算。整體設計讓多項式運算可以用接近數學表示法的方式操作，程式可讀性也明顯提升。

在開發初期，我遇到的主要問題是 **物件複製導致的記憶體錯誤**。因為 `Polynomial` 內部包含會動態配置節點的結構，如果只用編譯器預設的拷貝行為，就會變成「多個物件指向同一批節點」的情況。當其中一個物件解構或釋放節點時，另一個物件還以為自己擁有那段記憶體，最後就可能造成重複釋放或不明的記憶體錯誤（例如 `_UNKNOWN_BLOCK` 這類問題）。

因此我在修正過程中，實際理解並套用了 C++ 常說的 **三法則（Rule of Three）**：  
只要類別內部「自己管理資源」（例如動態記憶體、檔案、網路連線等），就必須同時正確實作：
- **拷貝建構子（Copy Constructor）**
- **指定運算子（Copy Assignment Operator）**
- **解構子（Destructor）**

這三者缺一不可，才能確保物件在「複製、指定、生命週期結束」時，資源都能被正確管理，不會互相干擾。

在這個作業中，我也更明確分辨了：
1. **淺拷貝（Shallow Copy）**：只複製指標（或內部結構的位址/連結），會導致多個物件共用同一份資料，容易發生重複釋放與資料互相污染。  
2. **深拷貝（Deep Copy）**：複製時重新建立自己的節點/內容，讓每個物件彼此獨立，才符合「各自擁有自己資源」的期待。  
3. 本次實作並不是用動態陣列的倍增（`capacity *= 2`）策略，而是使用 **鏈結串列節點** 來管理項目；效能表現主要取決於插入時的走訪成本。不過程式另外加入了 **可用節點回收（AvailableList / free list）** 的設計，把釋放的節點先回收起來，下次需要新節點時優先重用，能減少 `new/delete` 的頻率，讓記憶體配置更穩定。

透過這次不斷的測試與除錯，我不只完成了功能，更重要的是對「類別設計要怎麼負責任地管理資源」有了更扎實的理解。未來如果再遇到需要自行管理記憶體或資源的情境，我會優先確認拷貝語意（copy semantics）與生命週期管理是否完整，避免同類型錯誤再次發生。

