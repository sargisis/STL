#include "Vector.h"



// vector constructors 
template<typename T,typename Allocator>
g3::vector<T,Allocator>::vector()
    : size_{0}
    , capacity_{0}
    , arr_{nullptr}
{}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::vector(const vector& rhv)
    : size_{rhv.size_}
    , capacity_{rhv.capacity_}
    , arr_{new T[capacity_]}
{
    for (size_type i = 0; i < size_; ++i) {
        arr_[i] = rhv.arr_[i];
    }
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::vector(vector&& rhv)  
    : size_{std::move(rhv.size_)}
    , capacity_{std::move(rhv.capacity_)}
    , arr_{std::move(rhv.arr_)}
{
    size_ = 0; 
    capacity_ = 0; 
    arr_ = nullptr;
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::vector(std::initializer_list<value_type> init) 
    : size_{init.size()}
    , capacity_{init.size()}
    , arr_{new T[init.size()]}
{
    std::copy(init.begin() , init.end() , arr_);
}

template<typename T ,typename Allocator>
g3::vector<T,Allocator>::vector(size_type size , const_reference val) {
    for (size_type i = 0; i < size_; ++i) {
        this->arr_[i] = val; 
    }
}

template<typename T, typename Allocator>
template<typename InputIt>
g3::vector<T,Allocator>::vector(InputIt first , InputIt last) {
    for (auto it = first; it != last; ++it) {
        push_back(*first);
    }
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::~vector() {
    clear();
}
// end constructors

// vector operators assigments 

template<typename T, typename Allocator>
const g3::vector<T,Allocator>& g3::vector<T,Allocator>::operator=(const vector& rhv) {
    if (this != &rhv) {
        this->clear();
        size_ = rhv.size_;
        capacity_ = rhv.capacity_;

        arr_ = new T[capacity_];
        for (size_type i = 0; i < size_; ++i ) {
            arr_[i] = rhv.arr_[i];
        }
    }
    return *this; 
}

template<typename T, typename Allocator>
const g3::vector<T,Allocator>& g3::vector<T,Allocator>::operator=(vector&& rhv) {
    
    if (this != &rhv) {
        this->clear();
        size_ = std::move(rhv.size_);
        capacity_ = std::move(rhv.capacity_);
        arr_ = std::move(rhv.arr_);

        size_ = 0; 
        capacity_ = 0; 
        arr_ = nullptr;
    }
    return *this; 
}
// end assigments 

// get_allocator 

template<typename T , typename Allocator>
g3::vector<T,Allocator>::allocator_type g3::vector<T,Allocator>::get_allocator() {
    return alloc;
}

// end get_allocator

// element access functions 

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::at(size_type pos ) {
    return arr_[pos];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::at(size_type pos ) const{
    return arr_[pos];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::operator[](size_type pos) {
    return arr_[pos];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::operator[](size_type pos) const {
    return arr_[pos];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::front() {
    return arr_[0];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::front() const{
    return arr_[0];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::back() {
    return arr_[size_ - 1];
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::back() const {
    return arr_[size_ - 1];
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::begin() {
    return iterator(arr_);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::begin() const {
    return const_iterator(arr_);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::cbegin() const {
    return const_iterator(arr_);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::end() {
    return iterator(arr_ + size_);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::end() const{
    return const_iterator(arr_ + size_);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::cend() const{
    return const_iterator(arr_ + size_);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::rbegin() {
    return iterator(arr_ - 1);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::rbegin() const {
    return const_iterator(arr_ - 1);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::crbegin() const {
    return const_iterator(arr_ - 1);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::rend() {
    return iterator(arr_ + size_ - 1);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::rend() const {
    return const_iterator(arr_ + size_ - 1);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::crend() const {
    return const_iterator(arr_ + size_ - 1);
}

// end access element functions 

// capacity's
template<typename T,typename Allocator>
bool g3::vector<T,Allocator>::empty() const {
    return size() == 0;
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::size_type g3::vector<T,Allocator>::size() const {
    return size_;
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::size_type g3::vector<T,Allocator>::capacity() const {
    return capacity_;
}

template<typename T, typename Allocator>
void g3::vector<T,Allocator>::reserve(size_type new_cap) {
    if (new_cap < size_) {
        size_ = new_cap;
    }else if (new_cap > size_) {
        if (new_cap > capacity_) {
            capacity_ = (new_cap == 0) ? 1 : new_cap * 2; 
        
            T* tmp = new T[capacity_];
            for (size_type i = 0; i < size_; ++i ) {
                tmp[i] = arr_[i];    
            }
            delete[] arr_;
            arr_ = tmp; 
            tmp = nullptr;
        }
    }
}

// end capacity's

// clear //

template<typename T, typename Allocator>
void g3::vector<T,Allocator>::clear() noexcept {
    delete[] arr_;
    size_ = 0; 
    capacity_ = 0; 
    arr_ = nullptr;
}

// insert's and erase  

template<typename T, typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::insert(const_iterator pos , const_reference val) {
    
    size_type index = pos.ptr - arr_;

    if (size_ == capacity_) {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
    }

    for (size_type i = size_; i >= index; --i) {
        arr_[i] = std::move(arr_[i - 1]);
    }

    arr_[index] = val; 
    ++size_;
    return begin() + index; 
}


template<typename T, typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::insert(const_iterator pos , size_type count ,const_reference val) {
     size_type index = pos.ptr - arr_;
    
    if (size_ > capacity_) {
        reserve(size_);
    }

    for (size_type i = size_ + count - 1; i > index + count - 1; --i) {
        arr_[i] = std::move(arr_[i - count]);
    }
    for (size_type i = index; i < index + count; ++i) {
        arr_[i] = val;
    }
    ++size_;

    return begin() + index;
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::insert(const_iterator pos , std::initializer_list<value_type> init) {
    size_type index = pos.ptr - arr_;
    size_t count = init.size();
    if (size_ + count > capacity_)
    {  
        reserve(size_ + count);
    }

    for (size_type i = size_; i > index; --i)
    {
        arr_[i + count - 1] = std::move(arr_[i - 1]);
    }

    auto it = init.begin();

    for (size_type i = index; i < count + index; ++i)
    {
        arr_[i] = *it++;
    }

    size_ += count;
    
    
    
    return begin() + index;
}

template<typename T, typename Allocator>
template<typename InputIt> 
 g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
    size_type index = pos.ptr - arr_;

    size_type count = 0;
    for (InputIt it = first; it != last; ++it) {
        ++count;
    }

    if (size_ + count > capacity_) {
        reserve(size_ + count);
    }

    
    for (size_type i = size_ + count - 1; i >= index + count; --i) {
        arr_[i] = std::move(arr_[i - count]);
    }

    size_type i = index;
    for (InputIt it = first; it != last; ++it, ++i) {
        arr_[i] = std::move(it);
    }

    size_ += count;  

    return begin() + index;
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::erase(const_iterator pos) {
    size_type index = pos.ptr - arr_;
    for(size_type i = index; i < size_; ++i) {
        arr_[i] = arr_[i + 1];
    }
    --size_;
   return begin() + index;
}

template<typename T, typename Allocator>
g3::vector<T, Allocator>::iterator g3::vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
    size_type count = 0;
    for (auto it = first; it != last; ++it) {
        ++count;
    }
    iterator it; 
    size_ -= count;
    return it; 
}


// end insert and erase

// push element functions

template<typename T, typename Allocator>
void g3::vector<T,Allocator>::push_back(const_reference val) {
    if (size_ == capacity_) {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ *= 2;
    }

    T* tmp = new T[capacity_];
    for (size_type i = 0; i < size_; ++i) {
        tmp[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = tmp; 
    tmp = nullptr; 

    arr_[size_] = val;
    ++size_;
} 

template<typename T, typename Allocator>
void g3::vector<T, Allocator>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template<typename T, typename Allocator>
void g3::vector<T,Allocator>::resize(size_type new_size , const_reference val) {
    if (new_size < size_) {
        size_ = new_size; 
    } else if (new_size > size_) {
        if (new_size > capacity_) {
            capacity_ = new_size * 2; 
        }
        T* tmp = new T[capacity_];
        for (size_type i =0 ; i < size_; ++i) {
            tmp[i] = arr_[i]; 
        }
        delete[] arr_;
        arr_ = tmp; 
        tmp = nullptr;

        for (size_type i = size_; i < new_size; ++i) {
            arr_[i] = val; 
        }
      size_ = new_size; 
    }
}
// end push element functions

// compare function 
template<typename T, typename Allocator>
int g3::vector<T,Allocator>::compare(const vector& other) const {
    if (arr_ < other.arr_) {
        return -1;
    }else if (arr_ > other.arr_) {
        return 1;
    }
    return 0; 
}

template<typename T, typename Allocator>
bool g3::vector<T,Allocator>::operator==(const vector& other) const {
    return compare(other) == 0; 
}

template<typename T, typename Allocator>
bool g3::vector<T,Allocator>::operator!=(const vector& other) const {
    return compare(other) != 0; 
}

template<typename T, typename Allocator>
bool g3::vector<T,Allocator>::operator<(const vector& other) const {
    return compare(other) < 0; 
}

template<typename T, typename Allocator>
bool g3::vector<T,Allocator>::operator<=(const vector& other) const {
    return compare(other) <= 0; 
}

template<typename T, typename Allocator>
bool g3::vector<T,Allocator>::operator>(const vector& other) const {
    return compare(other) > 0; 
}

template<typename T, typename Allocator>
bool g3::vector<T,Allocator>::operator>=(const vector& other) const {
    return compare(other) >= 0; 
}

// end compare functions 

// start write const_iterator 

// constructors 
template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_iterator::const_iterator(pointer ptr) 
 : ptr{ptr}
{}
//

// compare //

template<typename T, typename Allocator>
int g3::vector<T,Allocator>::const_iterator::compare(const const_iterator& other) const {
    if (ptr < other.ptr) {
        return -1;
    }else if (ptr > other.ptr) {
        return 1; 
    }
    return 0;
}

// end compare // 

// start operator's // 

template<typename T ,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::const_iterator::operator+(size_type n ) const {
    return const_iterator(ptr + n); 
}

template<typename T ,typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::const_iterator::operator-(size_type n ) const {
   return const_iterator(ptr - n);
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_iterator& g3::vector<T,Allocator>::const_iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::const_iterator::operator++(int) {
    const_iterator tmp = *this; 
    ++(*this);
    return const_iterator(tmp);
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_iterator& g3::vector<T,Allocator>::const_iterator::operator--() {
    return const_iterator(--ptr);
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::const_iterator g3::vector<T,Allocator>::const_iterator::operator--(int) {
    const_iterator tmp = *this; 
    --(*this);
    return const_iterator(tmp);
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::const_iterator::operator*() const {
    return *ptr; 
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::const_pointer g3::vector<T,Allocator>::const_iterator::operator->() const {
    return ptr; 
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::const_iterator::operator[](size_type pos) const {
    return ptr[pos];
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_iterator::operator==(const const_iterator& other) const {
    return compare(other) == 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_iterator::operator!=(const const_iterator& other) const {
    return compare(other) != 0;
}   

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_iterator::operator<(const const_iterator& other) const {
    return compare(other) < 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_iterator::operator<=(const const_iterator& other) const {
    return compare(other) <= 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_iterator::operator>(const const_iterator& other) const {
    return compare(other) > 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_iterator::operator>=(const const_iterator& other) const {
    return compare(other) >= 0; 
}

// end const_iterator

// start write iterator for const_iterator


// constructors 
template<typename T, typename Allocator>
g3::vector<T,Allocator>::iterator::iterator(pointer ptr)   
    : const_iterator(ptr)
{}

// end 

// start operators 

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::iterator::operator+(size_type n) const {
    return iterator(this->ptr + n);
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::iterator::operator-(size_type n) const {
    return iterator(this->ptr  - n);
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator& g3::vector<T,Allocator>::iterator::operator++() {
    iterator(this->ptr++);
    return *this; 
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::iterator::operator++(int) {
    iterator tmp = *this; 
    ++(*this);
    return iterator(tmp);
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator& g3::vector<T,Allocator>::iterator::operator--() {
    return iterator(this->ptr--);
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::iterator g3::vector<T,Allocator>::iterator::operator--(int) {
    iterator tmp = *this; 
    --(*this);
    return tmp;
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::iterator::operator*() {
    return *(this->ptr);
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::pointer g3::vector<T,Allocator>::iterator::operator->()  {
    return this->ptr; 
}

template<typename T , typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::iterator::operator[](size_type pos) const {
    return this->ptr[pos];
}

// end operators 

// end iterator for const_iterator


// start const_reverse_iterator

// constructors 
template<typename T ,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator::const_reverse_iterator(pointer ptr) 
    : ptr{ptr}
{}

// compare // 

template<typename T, typename Allocator>
int g3::vector<T,Allocator>::const_reverse_iterator::compare(const const_reverse_iterator& other) const {
    if (ptr < other.ptr) {
        return -1; 
    }else if (ptr > other.ptr) {
        return 1; 
    }
    return 0; 
}
// end compare // 

// start operators // 
template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator g3::vector<T,Allocator>::const_reverse_iterator::operator+(size_type n ) const {
    return const_reverse_iterator(this->ptr - n);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator g3::vector<T,Allocator>::const_reverse_iterator::operator-(size_type n ) const {
    return const_reverse_iterator(this->ptr + n);
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator& g3::vector<T,Allocator>::const_reverse_iterator::operator++() {
    --ptr; 
    return *this; 
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator g3::vector<T,Allocator>::const_reverse_iterator::operator++(int) {
    const_reverse_iterator tmp = *this; 
    --(*this);
    return tmp;
}


template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator& g3::vector<T,Allocator>::const_reverse_iterator::operator--() {
    ++ptr; 
    return *this; 
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reverse_iterator g3::vector<T,Allocator>::const_reverse_iterator::operator--(int) {
    const_reverse_iterator tmp = *this; 
    ++(*this);
    return tmp;
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::const_reverse_iterator::operator*() const{
    return *this; 
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_pointer g3::vector<T,Allocator>::const_reverse_iterator::operator->() const{
    return this->ptr; 
}

template<typename T,typename Allocator>
g3::vector<T,Allocator>::const_reference g3::vector<T,Allocator>::const_reverse_iterator::operator[](size_type pos) const {
    return this->ptr[pos];
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const {
    return compare(other) == 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const {
    return compare(other) != 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const {
    return compare(other) < 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const {
    return compare(other) <= 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const {
    return compare(other) > 0; 
}

template<typename T , typename Allocator>
bool g3::vector<T,Allocator>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const {
    return compare(other) >= 0; 
}

// end operators 

// end const_reverse_iterator

// start iterator for const_reverse_iterator

// constructor 

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator::reverse_iterator(pointer ptr){
    const_reverse_iterator(this->ptr);
}

// operators 
template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator g3::vector<T,Allocator>::reverse_iterator::operator+(size_type n) const {
    return reverse_iterator(this->ptr - n);
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator g3::vector<T,Allocator>::reverse_iterator::operator-(size_type n) const {
    return reverse_iterator(this->ptr + n);
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator& g3::vector<T,Allocator>::reverse_iterator::operator++() {
    this->ptr--;
    return  *this; 
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator g3::vector<T,Allocator>::reverse_iterator::operator++(int) {
  reverse_iterator tmp = *this; 
  --(*this);
  return tmp;  
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator& g3::vector<T,Allocator>::reverse_iterator::operator--() {
   this->ptr--;
   return *this; 
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reverse_iterator g3::vector<T,Allocator>::reverse_iterator::operator--(int) {
  reverse_iterator tmp = *this; 
  ++(*this);
  return tmp; 
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::reverse_iterator::operator*() {
   return *this;  
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::pointer g3::vector<T,Allocator>::reverse_iterator::operator->() {
   return this->ptr;  
}

template<typename T, typename Allocator>
g3::vector<T,Allocator>::reference g3::vector<T,Allocator>::reverse_iterator::operator[](size_type pos) const {
   return this->ptr[pos];
}

// end operators 

// end reverse_iterator 

// end iterators uraaa