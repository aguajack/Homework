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
