#include <iostream>
#include <vector>
#include <random>
#include <cmath>
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
        // 若 key 相同則不插入
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
};

int main() {
    vector<int> testN = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000000);

    cout << "n\tHeight\tHeight/log2(n)" << endl;

    for (int n : testN) {
        BST tree;
        unordered_set<int> used;

        while ((int)used.size() < n) {
            int value = dist(gen);
            if (used.find(value) == used.end()) {
                used.insert(value);
                tree.Insert(value);
            }
        }

        int h = tree.Height();
        double ratio = h / log2((double)n);

        cout << n << "\t" << h << "\t" << ratio << endl;
    }

    return 0;
}
