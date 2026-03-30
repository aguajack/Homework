// Problem2.cpp
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

    cout << "=== Part (a): Height / log2(n) ===" << endl;
    cout << "n\tHeight/log2(n)" << endl;

    for (int i = 0; i < (int)testN.size(); ++i) {
        vector<int> data = GenerateRandomData(testN[i]);
        double ratio = TestBSTHeightRatio(data);
        cout << testN[i] << "\t" << ratio << endl;
    }

    cout << endl;
    cout << "=== Part (b): Delete node in BST ===" << endl;

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
