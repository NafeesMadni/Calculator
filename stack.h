#include "Doubly LL.h"

template<typename T> class stack {
    DoublyLL<T> list;
public:
    stack(){};
    
    stack(const stack<T>& s2);
    
    stack& operator= (const stack<T>& s2);

    bool isEmpty() { 
        return list.isEmpty();
    }
    void push(const T val);
    bool pop(T& val);
    T top();
    ~stack() {};
};

template<typename T> stack<T> :: stack(const stack<T>& rhs) {
    this -> list = rhs.list;
}

template<typename T> stack<T>& stack<T> :: operator=(const stack<T>& rhs) {
    if(&rhs == this) return *this;
    this -> list = rhs.list;
}

template<typename T> T stack<T> :: top() {
    T temp;
    if(isEmpty()) return temp;
    pop(temp);
    push(temp);
    return temp;
}

template<typename T> void stack<T> :: push(const T val) {
    list.insertAtHead(val);
}

template<typename T> bool stack<T> :: pop(T& val) {
    if(list.isEmpty()) return false;
    
    T temp;
    list.removeHead(temp);
    val = temp;
    return true;
}
