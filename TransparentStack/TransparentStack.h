#ifndef TRANSPARENT_STACK_H
#define TRANSPARENT_STACK_H
#include <stack>
#include <stdexcept>

using namespace std;

template <typename T>
class TransparentStack: public stack<T> {
public:
    T peek_at(size_t pos) const {
        if(pos >= this->size()) {
            throw invalid_argument("Position isn't there.");
        }
        return this->c.at(pos);
    };
};

#endif
