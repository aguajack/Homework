#include<iostream>
#include<string>
using namespace std;
void powerset(string a,int index,string current) {
    if (index == a.size()) {
        cout << current << endl;
        return;
    }
    else {
        powerset(a, index + 1, current);
        powerset(a, index + 1, current + a[index]);
    }
}
int main() {
    string s;
    cin >>s;
    powerset(s,0,"");
    return 0;
}
