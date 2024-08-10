#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "list.h"
#include <memory>

namespace g3
{

    template <typename T, typename Allocator>
    list<T, Allocator>::list(const Allocator &s)
        : head(nullptr), tail(nullptr), size_(0), alloc_(s)
    {
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::list(size_type n, const Allocator &alloc)
        : head(nullptr), tail(nullptr), size_(0), alloc_(alloc)
    {
        for (size_t i = 0; i < n; ++i)
        {
            Node *new_node = alloc_.allocate(1);
            alloc_.construct(new_node, T());

            if (tail)
            {
                tail->next = new_node;
                new_node->prev = tail;
            }
            else
            {
                head = new_node;
            }

            tail = new_node;
            ++size_;
        }
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::list(size_type n, const_reference value, const Allocator &alloc)
        : head(nullptr), tail(nullptr), size_(0), alloc_(alloc)
    {
        for (size_t i = 0; i < n; ++i)
        {
            push_back(value);
        }
    }

    template <typename T, typename Allocator>
    template <typename InputIt>
    list<T, Allocator>::list(InputIt first, InputIt last, const Allocator &alloc)
        : head(nullptr), tail(nullptr), size_(0), alloc_(alloc)
    {
        for (auto it = first; it != last; ++it)
        {
            push_back(*it);
        }
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::list(std::initializer_list<T> ilist, const Allocator &alloc)
        : head(nullptr), tail(nullptr), size_(0), alloc_(alloc)
    {
        for (const auto &x : ilist)
        {
            push_back(x);
        }
    }

    // Copy constructor
    template <typename T, typename Allocator>
    list<T, Allocator>::list(const list &x)
        : head(nullptr), tail(nullptr), size_(0), alloc_(x.alloc_)
    {
        Node *current = x.head;
        while (current != nullptr)
        {
            push_back(current->val);
            current = current->next;
        }
    }

    // Move constructor
    template <typename T, typename Allocator>
    list<T, Allocator>::list(list &&x)
        : head(nullptr), tail(nullptr), size_(0), alloc_(std::move(x.alloc_))
    {
        head = std::move(x.head);
        tail = std::move(x.tail);
        size_ = std::move(x.size_);

        x.head = nullptr;
        x.tail = nullptr;
        x.size_ = 0;
    }

    // Copy assignment operator
    template <typename T, typename Allocator>
    list<T, Allocator> &list<T, Allocator>::operator=(const list &x)
    {
        if (this != &x)
        {
            clear();
            for (Node *curr = x.head; curr != nullptr; curr = curr->next)
            {
                push_back(curr->val);
            }
            alloc_ = x.alloc_;
            size_ = x.size_;
        }
        return *this;
    }

    // Move assignment operator
    template <typename T, typename Allocator>
    list<T, Allocator> &list<T, Allocator>::operator=(list &&x)
    {
        if (this != &x)
        {
            clear();
            head = std::move(x.head);
            tail = std::move(x.tail);
            size_ = std::move(x.size_);
            alloc_ = std::move(x.alloc_);

            x.head = nullptr;
            x.tail = nullptr;
            x.size_ = 0;
        }
        return *this;
    }

    // Destructor
    template <typename T, typename Allocator>
    list<T, Allocator>::~list()
    {
        clear();
    }

    // Element Access
    template <typename T, typename Allocator>
    typename list<T, Allocator>::reference list<T, Allocator>::front()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        return head->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reference list<T, Allocator>::front() const
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        return head->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reference list<T, Allocator>::back()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        return tail->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reference list<T, Allocator>::back() const
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        return tail->val;
    }

    // Modifiers
    template <typename T, typename Allocator>
    template <typename... Args>
    typename list<T, Allocator>::reference list<T, Allocator>::emplace_front(Args &&...args)
    {
        Node *new_node = new Node(std::forward<Args>(args)...);
        new_node->next = head;
        if (head)
        {
            head->prev = new_node;
        }
        else
        {
            tail = new_node;
        }
        head = new_node;
        ++size_;
        return new_node->val;
    }

    template <typename T, typename Allocator>
    template <typename... Args>
    typename list<T, Allocator>::reference list<T, Allocator>::emplace_back(Args &&...args)
    {
        Node *new_node = new Node(std::forward<Args>(args)...);
        new_node->prev = tail;
        if (tail)
        {
            tail->next = new_node;
        }
        else
        {
            head = new_node;
        }
        tail = new_node;
        ++size_;
        return new_node->val;
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::push_front(const_reference x)
    {
        emplace_front(x);
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::push_front(rvalue_reference x)
    {
        emplace_front(std::move(x));
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::pop_front()
    {
        if (head)
        {
            Node *old_node = head;
            head = head->next;
            if (head)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }
            delete old_node;
            --size_;
        }
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::push_back(const_reference x)
    {
        emplace_back(x);
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::push_back(rvalue_reference x)
    {
        emplace_back(std::move(x));
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::pop_back()
    {
        if (tail)
        {
            Node *old_node = tail;
            tail = tail->prev;
            if (tail)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            delete old_node;
            --size_;
        }
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::swap(list &other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
        std::swap(alloc_, other.alloc_);
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::clear() noexcept
    {
        while (!empty())
        {
            pop_front();
        }
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::size_type list<T, Allocator>::remove(const_reference value)
    {
        size_type removed = 0;
        Node *current = head;
        while (current)
        {
            if (current->val == value)
            {
                Node *temp = current;
                current = current->next;
                if (temp->prev)
                {
                    temp->prev->next = temp->next;
                }
                else
                {
                    head = temp->next;
                }
                if (temp->next)
                {
                    temp->next->prev = temp->prev;
                }
                else
                {
                    tail = temp->prev;
                }
                delete temp;
                ++removed;
                --size_;
            }
            else
            {
                current = current->next;
            }
        }
        return removed;
    }

    // Capacity
    template <typename T, typename Allocator>
    bool list<T, Allocator>::empty() const noexcept
    {
        return size_ == 0;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::size_type list<T, Allocator>::size() const noexcept
    {
        return size_;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::size_type list<T, Allocator>::max_size() const noexcept
    {
        return std::allocator_traits<Allocator>::max_size(alloc_);
    }

    // Operations
    template <typename T, typename Allocator>
    void list<T, Allocator>::merge(list &x)
    {
        merge(std::move(x));
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::merge(list &&x)
    {
        if (this == &x)
        {
            return;
        }

        Node *new_head = nullptr;
        Node *new_tail = nullptr;

        Node *l1 = head;
        Node *l2 = x.head;

        while (l1 && l2)
        {
            if (l1->val <= l2->val)
            {
                if (!new_head)
                {
                    new_head = l1;
                    new_tail = l1;
                }
                else
                {
                    new_tail->next = l1;
                    l1->prev = new_tail;
                    new_tail = l1;
                }
                l1 = l1->next;
            }
            else
            {
                if (!new_head)
                {
                    new_head = l2;
                    new_tail = l2;
                }
                else
                {
                    new_tail->next = l2;
                    l2->prev = new_tail;
                    new_tail = l2;
                }
                l2 = l2->next;
            }
        }

        while (l1)
        {
            new_tail->next = l1;
            l1->prev = new_tail;
            new_tail = l1;
            l1 = l1->next;
        }

        while (l2)
        {
            new_tail->next = l2;
            l2->prev = new_tail;
            new_tail = l2;
            l2 = l2->next;
        }

        head = new_head;
        tail = new_tail;

        x.head = nullptr;
        x.tail = nullptr;
        x.size_ = 0;

        size_ += x.size_;
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::sort()
    {
        std::vector<T, Allocator> tempVec(begin(), end(), alloc_);
        std::sort(tempVec.begin(), tempVec.end());
        assign(tempVec.begin(), tempVec.end());
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::allocator_type list<T, Allocator>::get_allocator() const noexcept
    {
        return alloc_;
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::assign(size_type n, const_reference t)
    {
        clear();
        for (size_t i = 0; i < n; ++i)
        {
            push_back(t);
        }
    }

    template <typename T, typename Allocator>
    template <typename InputIt>
    void list<T, Allocator>::assign(InputIt first, InputIt last)
    {
        clear();
        for (auto it = first; it != last; ++it)
        {
            push_back(*it);
        }
    }

    template <typename T, typename Allocator>
    void list<T, Allocator>::assign(std::initializer_list<T> ilist)
    {
        clear();
        for (const auto &x : ilist)
        {
            push_back(x);
        }
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::iterator list<T, Allocator>::begin() noexcept
    {
        return iterator(head);
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_iterator list<T, Allocator>::begin() const noexcept
    {
        return const_iterator(head);
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_iterator list<T, Allocator>::cbegin() const noexcept
    {
        return const_iterator(head);
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::iterator list<T, Allocator>::end() noexcept
    {
        return iterator(nullptr);
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_iterator list<T, Allocator>::end() const noexcept
    {
        return const_iterator(nullptr);
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_iterator list<T, Allocator>::cend() const noexcept
    {
        return const_iterator(nullptr);
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::reverse_iterator list<T, Allocator>::rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::reverse_iterator list<T, Allocator>::rend() noexcept
    {
        return reverse_iterator(begin());
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_reverse_iterator list<T, Allocator>::crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_reverse_iterator list<T, Allocator>::crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    template <typename T, typename Allocator>
    template <typename... Args>
    typename list<T, Allocator>::iterator list<T, Allocator>::emplace(const_iterator position, Args &&...args)
    {
        Node *newNode = new Node(std::forward<Args>(args)...);
        Node *posNode = position.current;

        if (posNode == head)
        {
            newNode->next = head;
            head = newNode;
            if (!tail)
            {
                tail = newNode;
            }
        }
        else
        {
            Node *prev = head;
            while (prev->next != posNode)
            {
                prev = prev->next;
            }
            prev->next = newNode;
            newNode->next = posNode;
        }

        return iterator(newNode);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator position, const_reference x)
    {
        return emplace(position, x);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator position, rvalue_reference x)
    {
        return emplace(position, std::move(x));
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator position, size_type n, const_reference x)
    {
        iterator it = position;
        for (size_type i = 0; i < n; ++i)
        {
            it = emplace(it, x);
        }
        return it;
    }

    template <typename T, typename Allocator>
    template <class InputIt>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator position, InputIt first, InputIt last)
    {
        iterator it = position;
        for (InputIt iter = first; iter != last; ++iter)
        {
            it = emplace(it, *iter);
        }
        return it;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator position, std::initializer_list<T> il)
    {
        return insert(position, il.begin(), il.end());
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator position)
    {
        Node *posNode = position.current;
        if (!posNode)
        {
            return iterator(nullptr);
        }

        if (posNode == head)
        {
            head = head->next;
            if (head == nullptr)
            {
                tail = nullptr;
            }
        }
        else
        {
            Node *prev = head;
            while (prev->next != posNode)
            {
                prev = prev->next;
            }
            prev->next = posNode->next;
            if (posNode == tail)
            {
                tail = prev;
            }
        }

        delete posNode;
        return iterator(head);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator first, const_iterator last)
    {
        while (first != last)
        {
            first = erase(first);
        }
        return iterator(last.current);
    }
    template <typename T, typename Allocator>
    list<T, Allocator>::const_iterator::const_iterator(Node *node)
        : node_{node}
    {
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_iterator::const_reference list<T, Allocator>::const_iterator::operator*() const
    {
        return node_->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_iterator::const_pointer list<T, Allocator>::const_iterator::operator->() const
    {
        return &(node_->val);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_iterator &list<T, Allocator>::const_iterator::operator++()
    {
        node_ = node_->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_iterator list<T, Allocator>::const_iterator::operator++(int)
    {
        const_iterator tmp = *this;
        node_ = node_->next;
        return tmp;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_iterator &list<T, Allocator>::const_iterator::operator--()
    {
        node_ = node_->prev;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_iterator list<T, Allocator>::const_iterator::operator--(int)
    {
        const_iterator tmp = *this;
        node_ = node_->prev;
        return tmp;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::const_iterator::operator==(const_iterator &other) const
    {
        return this->node_ == other.node_;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::const_iterator::operator!=(const_iterator &other) const
    {
        return this->node_ != other.node_;
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::iterator::iterator(Node *node)
        : const_iterator(node)
    {
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator::reference list<T, Allocator>::iterator::operator*() const
    {
        return this->node_->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator::pointer list<T, Allocator>::iterator::operator->() const
    {
        return &(this->node_->val);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator &list<T, Allocator>::iterator::operator++()
    {
        this->node_ = this->node_->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::iterator::operator++(int)
    {
        iterator tmp = *this;
        this->node_ = this->node_->next;
        return tmp;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator &list<T, Allocator>::iterator::operator--()
    {
        this->node_ = this->node_->prev;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::iterator::operator--(int)
    {
        iterator tmp = *this;
        this->node_ = this->node_->prev;
        return tmp;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::iterator::operator!=(const iterator &other) const
    {
        return this->node_ != other.node_;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::iterator::operator==(const iterator &other) const
    {
        return this->node_ == other.node_;
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::const_reverse_iterator::const_reverse_iterator(Node *node)
        : node_{node}
    {
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reverse_iterator::const_reference list<T, Allocator>::const_reverse_iterator::operator*() const
    {
        return this->node_->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reverse_iterator::const_pointer list<T, Allocator>::const_reverse_iterator::operator->() const
    {
        return &(this->node_->val);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reverse_iterator &list<T, Allocator>::const_reverse_iterator::operator++()
    {
        this->node_ = this->node_->prev;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::const_reverse_iterator::operator++(int)
    {
        const_reverse_iterator tmp = *this;
        this->node_ = this->node_->prev;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reverse_iterator &list<T, Allocator>::const_reverse_iterator::operator--()
    {
        this->node_ = this->node_->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::const_reverse_iterator::operator--(int)
    {
        const_reverse_iterator tmp = *this;
        this->node_ = this->node_->next;
        return *this;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator &other) const
    {
        return this->node_ != other.node_;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::const_reverse_iterator::operator==(const const_reverse_iterator &other) const
    {
        return this->node_ == other.node_;
    }

    template <typename T, typename Allocator>
    list<T, Allocator>::reverse_iterator::reverse_iterator(Node *node)
        : const_reverse_iterator(node)
    {
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reverse_iterator::reference list<T, Allocator>::reverse_iterator::operator*() const
    {
        return this->node_->val;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reverse_iterator::pointer list<T, Allocator>::reverse_iterator::operator->() const
    {
        return &(this->node_->val);
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reverse_iterator &list<T, Allocator>::reverse_iterator::operator++()
    {
        this->node_ = this->node_->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reverse_iterator list<T, Allocator>::reverse_iterator::operator++(int)
    {
        iterator tmp = *this;
        this->node_ = this->node_->next;
        return tmp;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reverse_iterator &list<T, Allocator>::reverse_iterator::operator--()
    {
        this->node_ = this->node_->prev;
        return *this;
    }

    template <typename T, typename Allocator>
    typename list<T, Allocator>::reverse_iterator list<T, Allocator>::reverse_iterator::operator--(int)
    {
        iterator tmp = *this;
        this->node_ = this->node_->prev;
        return tmp;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::reverse_iterator::operator!=(const reverse_iterator &other) const
    {
        return this->node_ != other.node_;
    }

    template <typename T, typename Allocator>
    bool list<T, Allocator>::reverse_iterator::operator==(const reverse_iterator &other) const
    {
        return this->node_ == other.node_;
    }

}

#endif // __LIST_HPP__