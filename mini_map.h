#ifndef MINI_MAP
#define MINI_MAP

#include "mini_list.h"

template <typename T>
class MiniMap{
private:
    //Collisions will be handled by
    //a primitive version of a linked list
    Node<T> **hash_table;
    //size is the pre-allocated space
    //determined outside the class, not the current
    //mumber of items in the array
    int size;
    int num_of_items;

    //This is Jenkin's one-at-at-time hash,
    //adapted from 
    //https://en.wikipedia.org/wiki/Jenkins_hash_function
    int hash_function(const char* key){
        unsigned long hash, i;
        for(hash = i = 0; key[i] != 0; i++){
            hash += key[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        //hash is now almost 20 digits long,
        //so I took the mod operator to 
        //get a valid index
        return hash % size;
    }

public:
    //Initialize the size and set 
    //each pointer pointing to nullptr
    MiniMap(int size):size(size){
        //A little input validation
        if( !(size > 0) ) size = 100;
        hash_table = new Node<T>* [size];
        for(int i = 0; i < size; i++){
            hash_table[i] = nullptr;
        }
        num_of_items = 0;
    }
    ~MiniMap(){
        delete hash_table;
    }
    bool set(const char* key, T value){
        //Specs ask for a fixed size hash map, but
        //with collision handling this implementation
        //can support a variable-sized hash map.
        //Nevertheless we check to make sure 
        //num_of_items does not exceed size; 
        if (num_of_items == size) return false;
        int hash_value = hash_function(key);
        Node<T> *inserted_value = new Node<T>(key, new T(value), hash_table[hash_value], nullptr);
        //Check for collision and adjust prev pointer on following element to point to inserted element
        if(inserted_value->next != nullptr) inserted_value->next->prev = inserted_value;
        //Have the hash table point to the newly-inserted element
        hash_table[hash_value] = inserted_value;
        num_of_items++;
        return true;
    }
    T* get(const char* key){
        int hash_value = hash_function(key);
        Node<T> *ptr = hash_table[hash_value];
        while(ptr != nullptr){
            if(key == ptr->key){
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return nullptr;
    }
    T* remove(const char* key){
        int hash_value = hash_function(key);
        Node<T> *ptr = hash_table[hash_value];
        while(ptr != nullptr){
            if(key == ptr->key){
                T* return_value = ptr->value;
                //There are three cases for removing an element:
                //the element could be the first in the list,
                //the last in the list, or somewhere in the middle.
                //Here we cover all cases.
                //Element is first in the list: 
                if(ptr->prev == nullptr){
                    hash_table[hash_value] = ptr->next;
                    if(ptr->next != nullptr) ptr->next->prev = nullptr;
                }
                //Element is last in the list:
                if(ptr->next == nullptr){
                    if(ptr->prev != nullptr) ptr->prev->next = nullptr;
                }
                //Element is somewhere in between:
                if(ptr->prev != nullptr && ptr->next != nullptr){
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                }
                delete ptr;
                num_of_items--;
                return return_value;
            }
            ptr = ptr->next;
        }
        return nullptr;
    }

    float load(){
        return (float)num_of_items / size;
    }
};

#endif