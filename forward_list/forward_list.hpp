#include "../forward_list/forward_list.h"

template<typename T, typename Allocator>
g3::forward_list<T,Allocator>::forward_list()
    : m_head{nullptr}
    , m_size{0}
{}

template<typename T, typename Allocator>
g3::forward_list<T,Allocator>::forward_list(const forward_list& rhv)
    : m_head{nullptr}
    , m_size{rhv.m_size}
{
    if (rhv.m_head == nullptr) 
    {
        return;
    }
    Node* current = rhv.m_head;
    while (current != nullptr) 
    {
        push_back(current->val);
        current = current->next;
    }
}

template<typename T, typename Allocator>
g3::forward_list<T, Allocator>::forward_list(forward_list&& rhv) noexcept
    : m_head{std::move(rhv.m_head)}
    , m_size{rhv.m_size}
{

    rhv.m_head = nullptr;
    rhv.m_size = 0;
}

template<typename T, typename Allocator>
g3::forward_list<T,Allocator>::forward_list(std::initializer_list<T> init)
    : forward_list()
{
    for (auto& it : init) {
        push_back(it);
    }
}

template<typename T, typename Allocator>
template<typename InputIt>
g3::forward_list<T,Allocator>::forward_list(InputIt first , InputIt last)
    : forward_list()
{
    for (auto it = first; it != last; ++it) {
        push_back(*it);
    }
}

template<typename T, typename Allocator>
g3::forward_list<T,Allocator>::~forward_list() {
    clear();
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::begin() {
    return iterator(this->m_head);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_iterator g3::forward_list<T,Allocator>::begin() const {
    return const_iterator(this->m_head);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_iterator g3::forward_list<T,Allocator>::cbegin() const {
    return const_iterator(this->m_head);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::end() {
    return iterator(nullptr);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_iterator g3::forward_list<T,Allocator>::end() const{
    return const_iterator(nullptr);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_iterator g3::forward_list<T,Allocator>::cend() const{
    return const_iterator(nullptr);
}


template<typename T, typename Allocator>
g3::forward_list<T, Allocator>& g3::forward_list<T, Allocator>::operator=(const forward_list& rhv)
{
    if (this != &rhv)
    {
        this->m_head = rhv.m_head;
        this->m_size = rhv.m_size;
    }

    return *this;
}

template<typename T, typename Allocator>
g3::forward_list<T, Allocator>& g3::forward_list<T, Allocator>::operator=(forward_list&& rhv) noexcept
{
    if (this != &rhv) {
        this->clear();
        this->m_size = std::move(rhv.m_size);
        this->m_head = std::move(rhv.m_head);

        this->m_head = nullptr;
        this->m_size = 0;
    }
    return *this;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::allocator_type g3::forward_list<T,Allocator>::get_allocator() const
{
    return this->m_alloc;
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::assign(size_type count , const_reference value)
{
    this->clear();
    for (size_t i = 0; i < count; ++i) {
        this->m_head[i] = value;
    }
}

template<typename T, typename Allocator>
template<typename InputIt>
void g3::forward_list<T,Allocator>::assign(InputIt first , InputIt last)
{
    this->clear();
    for (auto it = first; it != last; ++it ) {
        push_back(*it);
    }
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::assign(std::initializer_list<value_type> ilist)
{
    this->clear();
    for (const auto& x : ilist) {
        push_back(x);
    }
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::reference g3::forward_list<T,Allocator>::front()
{
    return this->m_head->val;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_reference g3::forward_list<T,Allocator>::front() const
{
    return this->m_head->val;
}

template<typename T, typename Allocator>
bool g3::forward_list<T,Allocator>::empty() const noexcept
{
    return this->m_size == 0;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::size_type g3::forward_list<T,Allocator>::max_size() const noexcept
{
    std::numeric_limits<size_t>::max() / sizeof(Node);
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::clear() noexcept
{
    while(m_head) {
        Node* to_delete = this->m_head;
        this->m_head = this->m_head->next;
        delete to_delete;
    }
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::push_front(const_reference value)
{
    Node* new_node = new Node(value);
    new_node->next = this->head;
    this->head = new_node;
    ++m_size;
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::push_front(rvalue_reference value)
{
    Node* new_node = new Node(std::move(value));
    new_node->next = this->m_head;
    this->m_head = new_node;
    ++m_size;
}


template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::pop_front()
{
    if (this->m_head != nullptr) {
        Node* to_delete = this->m_head;
        this->m_head = this->m_head->next;
        delete to_delete;
    }
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::push_back(const_reference value)
{
    Node* new_node = new Node(value);
    if (this->m_head == nullptr) {
        this->m_head = new_node;
    }
    else {
        Node* current = this->m_head;
        while(current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    ++m_size;
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::push_back(rvalue_reference value)
{
    Node* new_node = new Node(value);
    if (this->m_head == nullptr) {
        this->m_head = new_node;
    }
    else {
        Node* current = this->m_head;
        while(current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    ++m_size;
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::pop_back()
{
    if (this->m_head == nullptr) {
        return;
    }
    if (this->m_head->next == nullptr) {
        delete this->m_head;
        this->m_head = nullptr;
    }
    else {
        Node* current = this->m_head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    --m_size;
}


template<typename T, typename Allocator>
void g3::forward_list<T, Allocator>::resize(size_type count) {
    if (this->m_size == count) {
        return;
    }

    if (this->m_size < count) {
        size_type nodesToAdd = count - this->m_size;
        Node* current = this->m_head;
        if (current == nullptr) {
            this->m_head = new Node(count);
            current = this->m_head;
            --nodesToAdd;
        } else {
            while (current->next != nullptr) {
                current = current->next;
            }
        }

        for (size_type i = 0; i < nodesToAdd; ++i) {
            current->next = new Node(count);
            current = current->next;
        }

    } else {
        size_type nodesToRemove = this->m_size - count;
        Node* current = this->m_head;
        for (size_type i = 0; i < count - 1; ++i) {
            current = current->next;
        }

        Node* toDelete = current->next;
        current->next = nullptr;

        while (toDelete != nullptr) {
            Node* next = toDelete->next;
            delete toDelete;
            toDelete = next;
        }
    }
    this->m_size = count;
}

template<typename T, typename Allocator>
void g3::forward_list<T,Allocator>::resize(size_type count , const_reference value) {
    if (this->m_size == count) {
        return;
    }
    if (this->m_size < count) {
        size_type add_nodes = count - this->m_size;
        Node* current = this->m_head;
        if (current == nullptr) {
            this->m_head = new Node(value);
            current = this->m_head;
            --add_nodes;
        } else {
            while (current->next != nullptr) {
                current = current->next;
            }
        }
        for (size_type i = 0; i < add_nodes; ++i) {
            current->next = new Node(value);
            current = current->next;
        }
    } else {
        size_type nodesToRemove = this->m_size - count;
        Node* current = this->m_head;
        for (size_type i = 0; i < count - 1; ++i) {
            current = current->next;
        }
        Node* toDelete = current->next;
        current->next = nullptr;
        while (toDelete != nullptr) {
            Node* next = toDelete->next;
            delete toDelete;
            toDelete = next;
        }
    }
    this->m_size = count;
}

template<typename T, typename Allocator>
void g3::forward_list<T, Allocator>::swap(forward_list& other) noexcept {
    Node* temp_head = this->m_head;
    this->m_head = other.m_head;
    other.m_head = temp_head;

    size_type temp_size = this->m_size;
    this->m_size = other.m_size;
    other.m_size = temp_size;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::insert_after(const_iterator pos , const_reference value) {
    if (this->m_head == nullptr && pos.ptr == nullptr)
    {
        this->m_head = new Node(value);
        ++m_size;
        return iterator(this->m_head);
    }

    Node* current = pos.ptr;
    Node* new_node = new Node(value);

    new_node->next = current->next;
    current->next = new_node;

    ++m_size;
    return iterator(new_node);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::insert_after(const_iterator pos, rvalue_reference value)
{
    if (this->m_head == nullptr && pos.ptr == nullptr)
    {
        this->m_head = new Node(value);
        ++m_size;
        return iterator(this->m_head);
    }

    Node* current = pos.ptr;
    Node* new_node = new Node(value);

    new_node->next = current->next;
    current->next = new_node;

    ++m_size;
    return iterator(new_node);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::insert_after(const_iterator pos , size_type count , const_reference value)
{
    if (this->m_head == nullptr && pos.ptr == nullptr)
    {
        this->m_head = new Node(value);
        ++m_size;
        return iterator(this->m_head);
    }
    size_type index = count - this->m_size;
    Node* current = pos.ptr;
    Node* new_node = new Node(value);

    if (current != nullptr )
    {
        for (size_type i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
    }
    if (current != nullptr)
    {
        new_node->next = current->next;
        current->next = new_node;
        ++m_size;
    }
    return iterator(new_node);
}

template<typename T, typename Allocator>
template<typename InputIt>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::insert_after(const_iterator pos , InputIt first , InputIt last)
{
    Node* current = pos.ptr;
    while (first != last)
    {
        Node* new_node = new Node(*first);

        new_node->next = current->next;
        current->next = new_node;

        current = new_node;
        ++first;
        ++m_size;
    }
    return iterator(current);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::insert_after(const_iterator pos , std::initializer_list<T> ilist)
{
    Node* current = pos.ptr;
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
        Node* new_node = new Node(*it);

        new_node->next = current->next;
        current->next = new_node;

        current = new_node;
        ++m_size;
    }

    return iterator(current);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::erase_after(const_iterator pos)
{
    Node* current = pos.ptr;
    while (current != nullptr && current->next != nullptr)
    {
        Node* to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
        --m_size;
    }
    return iterator(current->next);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::erase_after(const_iterator first , const_iterator last)
{
    Node* current = first.ptr;
    Node* end = last.ptr;
    while (current != nullptr && current->next != nullptr)
    {
        Node* to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
        --m_size;
    }
    return iterator(current->next);
}



template<typename T, typename Allocator>
g3::forward_list<T,Allocator>::const_iterator::const_iterator(Node* node)
    : ptr(node)
{}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_reference g3::forward_list<T,Allocator>::const_iterator::operator*() const {
    return ptr->val;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_pointer g3::forward_list<T,Allocator>::const_iterator::operator->() const {
    return &(ptr->val);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_iterator& g3::forward_list<T,Allocator>::const_iterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::const_iterator g3::forward_list<T,Allocator>::const_iterator::operator++(int) {
    const_iterator temp = *this;
    ptr = ptr->next;
    return temp;
}

template<typename T, typename Allocator>
bool g3::forward_list<T,Allocator>::const_iterator::operator!=(const const_iterator& other) const {
    return ptr != other.ptr;
}

template<typename T, typename Allocator>
bool g3::forward_list<T,Allocator>::const_iterator::operator==(const const_iterator& other) const {
    return ptr == other.ptr;
}


template<typename T, typename Allocator>
g3::forward_list<T,Allocator>::iterator::iterator(Node* node)
    : const_iterator(node)
{}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::reference g3::forward_list<T,Allocator>::iterator::operator*() const {
    return this->ptr->val;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::pointer g3::forward_list<T,Allocator>::iterator::operator->() const {
    return &(this->ptr->val);
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator& g3::forward_list<T,Allocator>::iterator::operator++()  {
    this->ptr = this->ptr->next;
    return *this;
}

template<typename T, typename Allocator>
typename g3::forward_list<T,Allocator>::iterator g3::forward_list<T,Allocator>::iterator::operator++(int)  {
    iterator temp = *this;
    this->ptr = this->ptr->next;
    return temp;
}

template<typename T, typename Allocator>
bool g3::forward_list<T,Allocator>::iterator::operator!=(const iterator& other) const {
    return this->ptr != other.ptr;
}

template<typename T, typename Allocator>
bool g3::forward_list<T,Allocator>::iterator::operator==(const iterator& other) const {
    return m_head == other.m_head;
}
