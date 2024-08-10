#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>
#include <deque>


template<typename T>
class queue {
private:
  std::deque<T> ob; 
public:
  using value_type = T;
  using size_type = std::size_t;
  using referance = value_type&;
  using const_referance = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
public:
 queue();
 queue(const queue&);
 queue(queue&&);
 ~queue();
 const queue& operator=(const queue<T>&);
 const queue& operator=(queue<T>&&);
 queue(std::initializer_list<T>);
 void push(const_referance);
 void pop();
 public:
 size_type front() const;
 referance size() const;
 void swap(const queue&);
 bool empty() const;
 void print() const; 
 referance operator [](size_type index);
 
};

template<typename T>
bool operator<(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator<=(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator>(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator>=(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator==(const queue<T> lhs, const queue<T> rhs);

template<typename T>
bool operator!=(const queue<T> lhs, const queue<T> rhs);


#include "Queue.hpp"

#endif //  __STACK_H__

