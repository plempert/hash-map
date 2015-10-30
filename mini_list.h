#ifndef MINI_LIST
#define MINI_LIST

template <typename T>
struct Node{
    T* value;
    const char *key;
    Node<T> *next;
    Node<T> *prev;
    Node(){
        value = nullptr;
        next = nullptr;
        prev = nullptr;        
    }
    Node(T* value):value(value){
        next = nullptr;
        prev = nullptr;
    }
    Node(const char* key, T* value, Node<T> *next, Node<T> *prev):key(key), value(value), next(next), prev(prev){}

};

#endif