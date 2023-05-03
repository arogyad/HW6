#include "./TransparentStack.h"
#include <iostream>

void Tests() {
    cout << "------Testing-------" << endl;
    TransparentStack<int> tt;
    tt.push(10);
    tt.push(20);
    tt.push(30);
    tt.push(40);
    tt.push(50);
    tt.push(60);

    assert(tt.peek_at(0) == 10);
    assert(tt.peek_at(2) == 30);
    assert(tt.peek_at(5) == 60);

    tt.pop();

    assert(tt.peek_at(0) == 10);
    assert(tt.peek_at(4) == 50);

    cout << endl;
    cout << "------Testing Completed-------" << endl;
}

int main() {
//    TransparentStack<unsigned int> t;
    Tests();
    return 0;
}