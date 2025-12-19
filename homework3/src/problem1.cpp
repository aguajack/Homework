#include <iostream>
#include <cmath>
#include <stdexcept>
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
    T& operator*() const {
        if (!current) throw runtime_error("dereference null iterator");
        return current->element;
    }
    T* operator->() const {
        if (!current) throw runtime_error("arrow on null iterator");
        return &(current->element);
    }
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
        if (idx < 0) return;
        ChainNode<T>* newNode = AvailableList<T>::getNode();
        if (!newNode) {
            newNode = new ChainNode<T>(element);
        } else {
            newNode->setElement(element);
            newNode->next = nullptr;
        }
        if (idx == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            ChainNode<T>* prev = head;
            for (int i = 0; i < idx - 1 && prev != nullptr; ++i) prev = prev->next;
            if (prev != nullptr) {
                newNode->next = prev->next;
                prev->next = newNode;
            } else {
                AvailableList<T>::getBack(newNode);
            }
        }
    }
    bool erase(int idx) {
        if (idx < 0 || !head) return false;
        if (idx == 0) {
            ChainNode<T>* del = head;
            head = head->next;
            del->next = nullptr;
            AvailableList<T>::getBack(del);
            return true;
        }
        ChainNode<T>* prev = head;
        for (int i = 0; i < idx - 1 && prev != nullptr; ++i) prev = prev->next;
        if (!prev || !prev->next) return false;
        ChainNode<T>* del = prev->next;
        prev->next = del->next;
        del->next = nullptr;
        AvailableList<T>::getBack(del);
        return true;
    }
};

class Polynomial {
public:
    struct Term {
        int coef;
        int exp;
        Term(int c = 0, int e = 0) : coef(c), exp(e) {}
    };

    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);

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

    void newTerm(int coef, int exp) {
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
                int newCoef = it1->coef + it2->coef;
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
                long long newCoef = 1LL * it1->coef * it2->coef;
                int newExp = it1->exp + it2->exp;
                if (newCoef != 0) result.newTerm((int)newCoef, newExp);
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

istream& operator>>(istream& is, Polynomial& poly) {
    int n;
    if (!(is >> n)) return is;
    AvailableList<Polynomial::Term>::getBack(poly.terms.release());
    for (int i = 0; i < n; ++i) {
        int c, e;
        is >> c >> e;
        poly.newTerm(c, e);
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
    int n = poly.terms.size();
    os << n;
    for (auto it = poly.begin(); it != poly.end(); ++it) {
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

    Polynomial CopyA(A);
    cout << "CopyA = " << CopyA << "\n";

    Polynomial Assign;
    Assign = B;
    cout << "Assign = " << Assign << "\n";

    float x;
    cout << "x = ";
    cin >> x;
    cout << "A(x) = " << A.Evaluate(x) << "\n";

    AvailableList<Polynomial::Term>::clearAll();
    return 0;
}

