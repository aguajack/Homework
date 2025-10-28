#include <iostream>
using namespace std;
class Polynomial;
class Term {
	friend Polynomial;
private:
	float coef;
	int exp;
};
class Polynomial {
public:
	Term* termArray;   // 指向非零項目的陣列
	int capacity;      // 陣列容量
	int terms;
private:
	Polynomial();                      // 建構 p(x)=0
	Polynomial Add(Polynomial poly);   // 回傳 this + poly
	Polynomial Mult(Polynomial poly);  // 回傳 this × poly
	float Eval(float f);               // 代入 f 計算 p(f)
	friend istream& operator>>(istream& input, Polynomial& poly); // 輸入
	friend ostream& operator<<(ostream& output, const Polynomial& poly); // 輸出
};
Polynomial::Polynomial() {
	capacity = 2;
	terms = 0;
	termArray = new Term[capacity];
	}
Polynomial::Add() {



}



int main() {
	int  A, B, C;

	cin >> A >> B;   // 可以用 >> 輸入兩個多項式
	C = A.Add(B);
	cout << C << endl; // 可以用 << 輸出結果
	return 0;

}
