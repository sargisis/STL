#ifndef _FORWARD_LIST_H
#define _FORWARD_LIST_H

#include <iostream>
#include <initializer_list>
#include <memory>
#include <limits>
#include <exception>


namespace g3 {

template <typename T, typename Allocator = std::allocator<T>>
class forward_list {
public:
   using value_type = T;
   using size_type = std::size_t;
   using reference = value_type&;
   using const_reference = const value_type&;
   using pointer = typename std::allocator_traits<Allocator>::pointer;
   using const_pointer = typename std::allocator_traits<Allocator>::const_pointer; 
   using difference_type = std::ptrdiff_t;
   using allocator_type = Allocator;
   using iterator_category = std::forward_iterator_tag;
   using rvalue_reference = value_type&&;

public: 
  class iterator; 
  class const_iterator;

public:
    forward_list();
    
    
    forward_list(const forward_list& rhv);
    
    forward_list(forward_list&& rhv) noexcept;
    
    forward_list(std::initializer_list<T> init);
    
    template <typename InputIt>
    forward_list(InputIt first, InputIt last);
    
    ~forward_list();

public:
    forward_list& operator=(const forward_list& rhv);
   
    forward_list& operator=(forward_list&& rhv) noexcept;
    
    allocator_type get_allocator() const;

public:
    void assign(size_type count, const_reference value);
   
    template <typename InputIt>
    void assign(InputIt first, InputIt last);
   
    void assign(std::initializer_list<value_type> ilist);

public:
    reference front();
    const_reference front() const;

public:
    iterator begin();
    const_iterator begin() const; 
    const_iterator cbegin() const;
    
    iterator end();
    const_iterator end() const; 
    const_iterator cend() const;

public:
     bool empty() const noexcept;
     size_type max_size() const noexcept;

public:
    void clear() noexcept;

public:
    iterator insert_after(const_iterator pos, const_reference value);

    iterator insert_after(const_iterator pos, rvalue_reference value);

    iterator insert_after(const_iterator pos, size_type count, const_reference value);

    template <class InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);

    iterator insert_after(const_iterator pos, std::initializer_list<T> ilist);

    iterator erase_after(const_iterator pos);

    iterator erase_after(const_iterator first, const_iterator last);

public:
    void push_front(const_reference value);

    void push_front(rvalue_reference value);

    void pop_front();

    void push_back(const_reference value);

    void push_back(rvalue_reference value);

    void pop_back();

public:
    void resize(size_type count);

    void resize(size_type count, const_reference value);

public:
    void swap(forward_list& other) noexcept;

private:
    struct Node {
        value_type val;
        Node* next;
        Node(const T& val) : val(val), next(nullptr) {}
    };
    Node* m_head;
    std::size_t m_size;
    allocator_type m_alloc;
};

template<typename T, typename Allocator>
class forward_list<T,Allocator>::const_iterator 
{
    friend class forward_list<value_type>;
protected:
    Node* ptr;  
private:
    const_iterator(Node* ptr);
public:
    const_iterator() : ptr(nullptr) {}
    const_iterator(const const_iterator& rhv) = default;
    const_iterator(const_iterator&& rhv) = default;

    const_iterator& operator=(const const_iterator& rhv) = default;
    const_iterator& operator=(const_iterator&& rhv) = default;  

    const_iterator& operator++();
    const_iterator operator++(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    bool operator==(const const_iterator& other) const; 
    bool operator!=(const const_iterator& other) const;
};

template<typename T, typename Allocator>
class forward_list<T,Allocator>::iterator : public forward_list<T,Allocator>::const_iterator 
{
    friend class forward_list<value_type>;
private:
    iterator(Node* ptr);
public:
    iterator() = default;
    iterator(const iterator& rhv) = default;
    iterator(iterator&& rhv) = default;

    iterator& operator=(const iterator& rhv) = default;
    iterator& operator=(iterator&& rhv) = default;

    reference operator*() const; 
    pointer operator->() const;

    iterator& operator++(); 
    iterator operator++(int);

    bool operator==(const iterator& other) const; 
    bool operator!=(const iterator& other) const; 
};

#include "forward_list.hpp"
}
#endif // _FORWARD_LIST_H
