#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstddef>
#include <memory>
#include <compare>
#include <iterator>
#include <initializer_list>
#include <type_traits>
#include <limits>
#include <expected>
#include <algorithm>


namespace g3 
{   
    template<typename T, typename Allocator = std::allocator<T>>
    class list 
    {
    public:
        // member types
        using value_type = T;
        using allocator_type = Allocator;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using rvalue_reference = value_type&&;

    public:
        // iterators
        class const_iterator; 
        class iterator; 
        class const_reverse_iterator;
        class reverse_iterator; 

    public:
        // construct/copy/destroy
        list() : list(Allocator()) {}
        explicit list(const Allocator& s);
        explicit list(size_type n, const Allocator& = Allocator());
        list(size_type n, const_reference value, const Allocator& = Allocator());

        template<class InputIt>
        list(InputIt first, InputIt last, const Allocator& = Allocator());
        list(const list& x);
        list(list&& x);
        list(std::initializer_list<T>, const Allocator& = Allocator());
        ~list();

        list& operator=(const list& x);
        list& operator=(list&& x);
        list& operator=(std::initializer_list<T>);
       
        template<class InputIt>
        void assign(InputIt first, InputIt last);
        void assign(size_type n, const_reference t);
        void assign(std::initializer_list<T>);

        allocator_type get_allocator() const noexcept;
 
    public:
        // iterators
        iterator begin() noexcept;
        const_iterator  begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
    
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;
 
    public:
        // capacity
        [[nodiscard]] bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        void resize(size_type size);
 
    public:
        // element access
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
    
    public:
        // modifiers
        template<class... Args> reference emplace_front(Args&&... args);
        template<class... Args> reference emplace_back(Args&&... args);
        void push_front(const_reference x);
        void push_front(rvalue_reference x);
        void pop_front();
        void push_back(const_reference x);
        void push_back(rvalue_reference x);
        void pop_back();
 
        template<class... Args> iterator emplace(const_iterator position, Args&&... args);
        iterator insert(const_iterator position, const_reference x);
        iterator insert(const_iterator position, rvalue_reference x);
        iterator insert(const_iterator position, size_type n, const_reference x);
        template<class InputIt>
        iterator insert(const_iterator position, InputIt first, InputIt last);
        iterator insert(const_iterator position, std::initializer_list<T> il);
        iterator erase(const_iterator position);
        iterator erase(const_iterator position, const_iterator last);
    
        void swap(list&);
        void clear() noexcept;
 
    public:
     
        size_type remove(const_reference value);
 
        void merge(list& x);
        void merge(list&& x);
 
        void sort();
    
        void reverse() noexcept;  

        private:
         struct Node 
        {   
            value_type val;
            Node* next; 
            Node* prev; 
            Node(const_reference val = T()) 
             : val{val}
             , next{nullptr}
             , prev{nullptr}
            {}
             template<class... Args>
             Node(Args&&... args) : val(std::forward<Args>(args)...)
             , next(nullptr) 
             {}
        };    

        private:
        Node* head; 
        Node* tail; 
        allocator_type alloc_;
        size_type size_;

    };

    template<typename T, typename Allocator>
    class list<T,Allocator>::const_iterator 
    {
        private:
        friend class list<T,Allocator>;

        public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using reference = value_type&;

        private:
        const_iterator( Node* node);

        public:
        const_iterator() = default;

        const_iterator(const const_iterator& rhv) = default;
        const_iterator(const_iterator&& rhv) = default;

        const_iterator& operator=(const const_iterator& rhv) = default;
        const_iterator& operator=(const_iterator&& rhv) = default; 

        public:
        const_reference operator*() const; 
        const_pointer operator->() const;

        public:
        const_iterator& operator++();
        const_iterator operator++(int);

        const_iterator& operator--();
        const_iterator operator--(int);

     public:
       bool operator==(const_iterator& other) const;
       bool operator!=(const_iterator& other) const; 

       protected:
       Node* node_;
    };
    
    template<typename T, typename Allocator>
    class list<T,Allocator>::iterator : public list<T,Allocator>::const_iterator 
    {
        friend class list<T,Allocator>;
        public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;

        private:
        iterator(Node* node);

        public:
        iterator() = default;
        iterator(const iterator& rhv) = default;
        iterator(iterator&& rhv) = default;

        iterator& operator=(const iterator& rhv) = default;
        iterator& operator=(iterator&& rhv) = default;
        

        public:
        reference operator*() const; 
        pointer operator->() const;

        iterator& operator++();
        iterator operator++(int);
        
        iterator& operator--();
        iterator operator--(int);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;


    };      

    template<typename T, typename Allocator>
    class list<T,Allocator>::const_reverse_iterator 
    {
        friend class list<T,Allocator>;
        public:

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;

        private:
        explicit const_reverse_iterator( Node* node);
        
        public:
        const_reverse_iterator() = default;
        const_reverse_iterator(const reverse_iterator& rhv) = default; 
        const_reverse_iterator(reverse_iterator&& rhv) = default; 

        const_reverse_iterator& operator=(const reverse_iterator& rhv) = default; 
        const_reverse_iterator& operator=(reverse_iterator& rhv) = default;

        const_reference operator*() const; 
        const_pointer operator->() const;

        const_reverse_iterator& operator++();
        const_reverse_iterator operator++(int);
        
        const_reverse_iterator& operator--();
        const_reverse_iterator operator--(int);

        bool operator==(const const_reverse_iterator& other) const;
        bool operator!=(const const_reverse_iterator& other) const;

        protected:
        Node* node_;
    };

    template<typename T, typename Allocator>
    class list<T,Allocator>::reverse_iterator : public list<T,Allocator>::const_reverse_iterator 
    {
        friend class list<T,Allocator>;
        public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;

        private:
        reverse_iterator(Node* node);
        
        public:
        reverse_iterator() = default;
        reverse_iterator(const iterator& rhv) = default;
        reverse_iterator(iterator&& rhv) = default;

        reverse_iterator& operator=(const iterator& rhv) = default;
        reverse_iterator& operator=(iterator&& rhv) = default;
        

        public:
        reference operator*() const; 
        pointer operator->() const;

        reverse_iterator& operator++();
        reverse_iterator operator++(int);
        
        reverse_iterator& operator--();
        reverse_iterator operator--(int);

        bool operator==(const reverse_iterator& other) const; 
        bool operator!=(const reverse_iterator& other) const;
    };  
}

#include "list.hpp"

#endif // __LIST_H__