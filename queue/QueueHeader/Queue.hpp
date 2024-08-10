#ifndef __QUEUE__HPP__
#define __QUEUE__HPP__

#include "Queue.h"


template<typename T>

queue<T>::queue()
    
{
    ob = nullptr;
} 

template<typename T>
queue<T>::queue(const queue& rhv) 

{
    ob = rhv.ob;
}

template<typename T>
queue<T>::queue(queue&& rhv) 
    : queue()

{
    ob = std::move(rhv.ob);
}

template<typename T>
queue<T>::~queue() {}

template<typename T>
queue<T>::queue(std::initializer_list<T> initlist)
   : ob{initlist}
{}
template<typename T>
const queue<T>& queue<T>::operator=(const queue& rhv){
    if (this != &rhv){
        
          for (const T& val : rhv){
              ob = rhv.ob;
          }
    }
     return *this; 
}

template<typename T>
const queue<T>& queue<T>::operator=(queue&& rhv){
        if (this != &rhv){

            for (const T& val : rhv){
                ob = std::move(rhv.ob);
            }
        }
    return *this; 
}
template<typename T>
queue<T>::size_type queue<T>::front() const {
    return ob.front();
}

template<typename T>
void queue<T>::swap(const queue& rhv){
     std::swap(ob , rhv.ob);
}

template<typename T>
bool queue<T>::empty() const {
     return ob.size();
}


template<typename T>
queue<T>::referance queue<T>::size() const {
    return ob.size();
    
}

template<typename T>
void queue<T>::push(const_referance elem){
   return ob.push_front(elem);
}

template<typename T>
void queue<T>::pop(){
    return ob.pop_front();
}

template<typename T>
void queue<T>::print() const
{   
    for(size_t i = 0; i < ob.size(); ++i){
        std::cout << ob[i] << " " << std::endl; 
    }
}

template<typename T>
queue<T>::referance queue<T>::operator[](size_type index) {
    return ob[index];
}


template<typename T>
bool operator<(const queue<T> lhs, const queue<T> rhs){
    return compare(lhs, rhs) < 0;
}

template<typename T>
bool operator>(const queue<T> lhs, const queue<T> rhs){
    return compare(lhs, rhs) > 0;
}

template<typename T>
bool operator<=(const queue<T> lhs, const queue<T> rhs){
    return compare(lhs, rhs) <= 0;
}

template<typename T>
bool operator>=(const queue<T> lhs, const queue<T> rhs){
    return compare(lhs, rhs) >= 0;
}

template<typename T>
bool operator==(const queue<T> lhs, const queue<T> rhs){
    return compare(lhs, rhs) == 0;
}

template<typename T>
bool operator!=(const queue<T> lhs, const queue<T> rhs){
    return compare(lhs, rhs) != 0;
}


#endif // 
