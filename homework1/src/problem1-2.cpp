#include <iostream>
using namespace std;


struct AckFrame {
    int mValue;     
    int nValue;    
    int stageFlag; 
};

const int MAX_STACK_SIZE = 100000;
AckFrame callStack[MAX_STACK_SIZE]; 
int stackTop = -1;                   

// 非遞迴 Ackermann 函數
int AckermannIterative(int m, int n) {
    int result = 0;
    stackTop = -1;  
    callStack[++stackTop] = { m, n, 0 }; 

    while (stackTop >= 0) {
        AckFrame current = callStack[stackTop--]; 

        if (current.mValue == 0) {
            result = current.nValue + 1;
            continue;
        }

        if (current.nValue == 0) {
         
            callStack[++stackTop] = { current.mValue - 1, 1, 0 };
            continue;
        }

        if (current.stageFlag == 0) {
            
            callStack[++stackTop] = { current.mValue, current.nValue, 1 };
            callStack[++stackTop] = { current.mValue, current.nValue - 1, 0 };
        } else {
         
            callStack[++stackTop] = { current.mValue - 1, result, 0 };
        }
    }

    return result;
}

int main() {
    cout << AckermannIterative(1, 2);
    return 0;
}
