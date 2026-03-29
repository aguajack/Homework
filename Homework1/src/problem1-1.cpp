
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;   // priority queue 是否為空
    virtual const T& Top() const = 0;   // 回傳最小元素
    virtual void Push(const T& x) = 0;  // 插入元素
    virtual void Pop() = 0;             // 刪除最小元素
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
        int size = heap.size() - 1;

        while (2 * index <= size) {
            int left = 2 * index;
            int right = 2 * index + 1;
            int smallerChild = left;

            if (right <= size && heap[right] < heap[left]) {
                smallerChild = right;
            }

            if (heap[smallerChild] < heap[index]) {
                swap(heap[smallerChild], heap[index]);
                index = smallerChild;
            } else {
                break;
            }
        }
    }

public:
    MinHeap() {
        heap.push_back(T()); // heap[0] 佔位
    }

    virtual ~MinHeap() {}

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

        int size = heap.size() - 1;
        heap[1] = heap[size];
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

    cout << "Top = " << h.Top() << endl; // 10

    h.Pop();
    cout << "Top after Pop = " << h.Top() << endl; // 20

    return 0;
}
