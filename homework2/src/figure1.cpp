#include <iostream>
#include <vector>
using namespace std;

// ===== 前置宣告 =====
class Polynomial;

// ===== Term 類別：表示多項式中的單一項 =====
class Term {
public:
    float coef;  // 係數
    int exp;     // 次方

    Term(float c = 0, int e = 0) {
        coef = c;
        exp = e;
    }
};

// ===== Polynomial 類別：表示整個多項式 =====
class Polynomial {
private:
    vector<Term> terms;  // 儲存多項式所有的項目
public:
    void newTerm(const float theCoef, const int theExp);
    Polynomial Add(const Polynomial& b);
    friend istream& operator>>(istream& is, Polynomial& poly);
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
};

// ===== 多載輸入運算子 =====
istream& operator>>(istream& is, Polynomial& poly) {
    int n;
    is >> n; // 讀入非零項的數量
    for (int i = 0; i < n; i++) {
        float c;
        int e;
        is >> c >> e;
        poly.newTerm(c, e);
    }
    return is;
}

// ===== 多載輸出運算子 =====
// ⚠️ 這裡改成沒有空格
ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms.size(); i++) {
        os << poly.terms[i].coef << "X^" << poly.terms[i].exp;
        if (i != poly.terms.size() - 1) // 項與項之間不加空格
            os << "+";
    }
    return os;
}

// ===== 新增多項式項目 =====
void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef != 0)
        terms.push_back(Term(theCoef, theExp));
}

// ===== 多項式相加 =====
Polynomial Polynomial::Add(const Polynomial& b) {
    Polynomial c;
    int i = 0, j = 0;

    while (i < terms.size() && j < b.terms.size()) {
        if (terms[i].exp == b.terms[j].exp) {
            float sum = terms[i].coef + b.terms[j].coef;
            if (sum != 0)
                c.newTerm(sum, terms[i].exp);
            i++;
            j++;
        }
        else if (terms[i].exp > b.terms[j].exp) {
            c.newTerm(terms[i].coef, terms[i].exp);
            i++;
        }
        else {
            c.newTerm(b.terms[j].coef, b.terms[j].exp);
            j++;
        }
    }

    // 加入剩餘項
    while (i < terms.size()) {
        c.newTerm(terms[i].coef, terms[i].exp);
        i++;
    }
    while (j < b.terms.size()) {
        c.newTerm(b.terms[j].coef, b.terms[j].exp);
        j++;
    }

    return c;
}

// ===== 主程式 =====
int main() {
    Polynomial A, B, C;

    cin >> A;
    cin >> B;

    C = A.Add(B);

    cout << C << endl;  // 最後輸出結果

    return 0;
}
