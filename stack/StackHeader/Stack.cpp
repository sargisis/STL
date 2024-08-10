#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "Stack.h"

template<typename T>
stack<T>::stack() 

{}

template<typename T>
stack<T>::stack(const stack& rhv)  
 : ob{rhv.ob}
{}

template<typename T>
stack<T>::stack(stack&& rhv) 
    : ob{std::move(rhv.ob)}
{}

template<typename T>
stack<T>::~stack() noexcept 
{}

template<typename T>
stack<T>::stack(std::initializer_list<T> initlist)        
    : ob(initlist.begin() , initlist.end())
{}
template<typename T>
const stack<T>& stack<T>::operator=(const stack& rhv){
    if (this != &rhv){
        ob = rhv.ob;
    }
    return *this; 
}

template<typename T>
const stack<T>& stack<T>::operator=(stack&& rhv){
    if (this != &rhv){
        ob = std::move(rhv.ob);
    }
    return *this; 
}

template<typename T>
stack<T>::referance stack<T>::top(){
    if (ob.empty()){
        throw std::out_of_range("stack::top(): stack is empty");
    }
    return ob.back();
}

template<typename T>
void stack<T>::_swap(const stack& rhv){
    std::swap(ob , rhv.ob);
}

template<typename T>
bool stack<T>::empty() {
    return ob.empty();
}

template<typename T>
stack<T>::size_type stack<T>::size() const {
    return ob.size();
}

template<typename T>
void stack<T>::push(const_referance elem){
    ob.push_back(elem);
}

template<typename T>
void stack<T>::pop(){
    if (!ob.empty()) {
        ob.pop_back();
    }
}

template<typename T>
stack<T>::referance stack<T>::operator[](size_type index) {
    return ob[index];
}


template<typename T>
void stack<T>::print() const {
    for (size_t i = 0; i < ob.size(); ++i ){
        std::cout << ob[i] << " " << std::endl; 
    }
}


template<typename T>
bool operator<( stack<T>& lhs,  stack<T> &rhs){
     return lhs.size() < rhs.size(); 
}

template<typename T>
bool operator<=( stack<T>& lhs,  stack<T>& rhs){
     return lhs.size() <= rhs.size();
}

template<typename T>
bool operator>( stack<T>& lhs,  stack<T>& rhs){
    return  lhs.size() > rhs.size();
}

template<typename T>
bool operator>=( stack<T>& lhs,  stack<T>& rhs){
    return lhs.size() >= rhs.size();
}

template<typename T>
bool operator==( stack<T>& lhs,  stack<T>& rhs){
    return lhs.size() == rhs.size();     
}

template<typename T>
bool operator!=( stack<T>& lhs,  stack<T>& rhs){
    return lhs.size() != rhs.size();
}


#endif // STACK_HPP__
