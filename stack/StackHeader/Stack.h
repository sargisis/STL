#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include <vector> 

template<typename T>

class stack {
private:
     std::vector<T> ob;
public:
  using value_type = T;
  using size_type = std::size_t;
  using referance = value_type&;
  using const_referance = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
public:
 stack();
 stack(const stack&);
 stack(stack&&);
 ~stack() noexcept;
 const stack& operator=(const stack<T>&);
 const stack& operator=(stack<T>&&);
 stack(std::initializer_list<T>);
 void push(const T&);
 void pop();
 public:
 referance top();
 size_type size() const;
 void _swap(const stack&);
 bool empty();
 void print() const;
 referance operator[](size_type index);

};

template<typename T>
bool operator<( stack<T>& lhs,  stack<T>& rhs);

template<typename T>
bool operator<=( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator>( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator>=( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator==( stack<T>& lhs, stack<T>& rhs);

template<typename T>
bool operator!=( stack<T>& lhs,  stack<T>& rhs);



#include "Stack.cpp"

#endif //  __STACK_H__

