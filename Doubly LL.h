#include <iostream>
#pragma once
using namespace std;

template<typename T>class Node{
public:
    T data;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
    explicit Node(T val): data(val) {};
};

template<typename T>class DoublyLL{
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int elements = 0;
public:
    
    DoublyLL() {};
    
    DoublyLL(const DoublyLL<T>& list);

    DoublyLL& operator= (const DoublyLL<T>& list);

    void insert(const T val);

    void insertAtHead(const T val);

    bool search(const T val) const;

    bool remove(const T val);

    bool removeHead(T& headData);

    bool isEmpty() { return elements == 0; }
    
    void Swap(DoublyLL& list2);

    template<typename out> friend ostream& operator<< (ostream& cout, const DoublyLL<out>& list);

    ~DoublyLL();
};

template<typename out> ostream& operator<< (ostream& cout, const DoublyLL<out>& list) {
    Node<out>* temp = list.head;
    while (temp != nullptr) {
        cout << temp -> data << " ";
        temp = temp -> next;
    } cout << endl;

    cout << "Head: " << list.head -> data << endl;
    cout << "Tail: " << list.tail -> data << endl;
    cout << "Elemments: " << list.elements << endl;

    return cout;
}

template<typename T> DoublyLL<T> :: DoublyLL(const DoublyLL<T>& list) {  
    elements = list.elements;  

    Node<T>* tempHead = list.head;  
    Node<T>* cur = new Node<T>(tempHead -> data);  
    tempHead = tempHead -> next;  

    head = tail = cur;  
        
    while (tempHead != nullptr) {  
        Node<T>* newNode = new Node<T>(tempHead -> data); 
        tail -> next = newNode;  
        newNode -> prev = tail;  
        tail = newNode;  

        tempHead = tempHead -> next;  
    }
} 

template<typename T> DoublyLL<T>& DoublyLL<T> :: operator= (const DoublyLL<T>& rhs) {  

    if(this == &rhs) return *this; 

    elements = rhs.elements; 
    
    while (head != nullptr) { 
        Node<T>* temp = head; 
        head = head -> next;  
        delete temp; 
    }  
    tail = nullptr;  

    Node<T>* tempHead = rhs.head; 
    Node<T>* cur = new Node<T>(tempHead -> data); 
    tempHead = tempHead -> next;  

    head = tail = cur;  
        
    while (tempHead != nullptr) {  
        Node<T>* newNode = new Node<T>(tempHead -> data);  
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;

        tempHead = tempHead -> next;
    }
    return *this;
}

template<typename T> void DoublyLL<T> :: insert(const T val){

    if (!elements) insertAtHead(val);
    else{
        Node<T>* newNode = new Node<T>(val);
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
        elements++;
    }
}

template<typename T> void DoublyLL<T> :: insertAtHead(const T val){
    Node<T>* newNode = new Node<T>(val);
    if(!elements) head = tail = newNode;
    else{
        newNode -> next = head;
        head -> prev = newNode;
        head = newNode;
    }
    elements++;
}

template<typename T> bool DoublyLL<T> :: search(const T val) const {
    Node<T>* temp = head;

    while (temp != nullptr) {
        if(temp -> data == val) return true;
        temp = temp -> next;
    }
    return false;
}

template<typename T> bool DoublyLL<T> :: remove(const T val) {
    if(elements == 0) return false;

    if(head -> data == val && elements == 1) {
        delete head;
        head = tail = nullptr;
        elements--;
        return true;
    }
    
    if(tail -> data == val) {
        Node<T>* temp = tail;
        tail = tail -> prev;
        tail -> next = nullptr;
        delete temp;
        elements--;
        return true;
    }

    Node<T>* cur = head;
    Node<T>* pre = nullptr;

    while (cur -> next != nullptr) {
        if(cur -> data == val) {
            pre -> next = cur -> next;
            cur -> next -> prev = pre;
            elements--;
            return true;
        }
        pre = cur;
        cur = cur -> next;
    }
    
    return false;
}

template<typename T> bool DoublyLL<T> :: removeHead(T& headData) {
    if(elements == 0) return false;

    headData = head ->data;
    if(elements == 1) {
        delete head;
        head = tail = nullptr;
        elements--;
        return true;
    }
    Node<T>* temp = head;

    head = head -> next;
    head -> prev = nullptr;
    delete temp;
    elements--;
    return true;
}
template<typename T> DoublyLL<T> :: ~DoublyLL() {

    while (head != nullptr) {
        Node<T>* temp = head;
        head = head -> next;
        delete temp;
    }
    tail = nullptr;
}