#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "List.h"
#include "DoubleNode.h"

template <typename T>
class DoubleLinkedList : public List<T>
{
public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    DoubleLinkedList(const DoubleLinkedList& other) : DoubleLinkedList()
    {
        for (DoubleNode<T>* node = other.head; node != nullptr; node = node->next)
        {
            pushBack(node->data);
        }
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other)
    {
        if (this != &other)
        {
            DoubleLinkedList copy(other);
            std::swap(head, copy.head);
            std::swap(tail, copy.tail);
            std::swap(count, copy.count);
        }
        return *this;
    }

    DoubleLinkedList(DoubleLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ~DoubleLinkedList() override { clear(); }

    void pushFront(const T& value) override
    {
        DoubleNode<T>* node = new DoubleNode<T>(value);
        node->next = head;

        if (head != nullptr)
        {
            head->prev = node;
        }
        else
        {
            tail = node;
        }

        head = node;
        ++count;
    }

    void pushBack(const T& value) override
    {
        DoubleNode<T>* node = new DoubleNode<T>(value);
        node->prev = tail;

        if (tail != nullptr)
        {
            tail->next = node;
        }
        else
        {
            head = node;
        }

        tail = node;
        ++count;
    }

    void insertAt(std::size_t index, const T& value) override
    {
        if (index > count)
        {
            throw std::out_of_range("DoubleLinkedList::insertAt: index out of range");
        }

        if (index == 0)
        {
            pushFront(value);
            return;
        }

        if (index == count)
        {
            pushBack(value);
            return;
        }

        DoubleNode<T>* current = nodeAt(index);
        DoubleNode<T>* node = new DoubleNode<T>(value);
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
        ++count;
    }

    bool remove(const T& value) override
    {
        for (DoubleNode<T>* node = head; node != nullptr; node = node->next)
        {
            if (node->data == value)
            {
                unlink(node);
                return true;
            }
        }
        return false;
    }

    bool removeAt(std::size_t index) override
    {
        if (index >= count)
        {
            return false;
        }

        unlink(nodeAt(index));
        return true;
    }

    void clear() override
    {
        DoubleNode<T>* node = head;
        while (node != nullptr)
        {
            DoubleNode<T>* next = node->next;
            delete node;
            node = next;
        }

        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    T& at(std::size_t index) override
    {
        if (index >= count)
        {
            throw std::out_of_range("DoubleLinkedList::at: index out of range");
        }
        return nodeAt(index)->data;
    }

    const T& at(std::size_t index) const override
    {
        if (index >= count)
        {
            throw std::out_of_range("DoubleLinkedList::at: index out of range");
        }
        return nodeAt(index)->data;
    }

    bool contains(const T& value) const override
    {
        for (DoubleNode<T>* node = head; node != nullptr; node = node->next)
        {
            if (node->data == value)
            {
                return true;
            }
        }
        return false;
    }

    std::size_t size() const override { return count; }
    bool empty() const override { return count == 0; }

    DoubleNode<T>* front() const { return head; }
    DoubleNode<T>* back() const { return tail; }

private:
    // Returns the node at the given valid index, walking from the closest end.
    DoubleNode<T>* nodeAt(std::size_t index) const
    {
        if (index < count / 2)
        {
            DoubleNode<T>* node = head;
            for (std::size_t i = 0; i < index; ++i)
            {
                node = node->next;
            }
            return node;
        }

        DoubleNode<T>* node = tail;
        for (std::size_t i = count - 1; i > index; --i)
        {
            node = node->prev;
        }
        return node;
    }

    void unlink(DoubleNode<T>* node)
    {
        if (node->prev != nullptr)
        {
            node->prev->next = node->next;
        }
        else
        {
            head = node->next;
        }

        if (node->next != nullptr)
        {
            node->next->prev = node->prev;
        }
        else
        {
            tail = node->prev;
        }

        delete node;
        --count;
    }

    DoubleNode<T>* head;
    DoubleNode<T>* tail;
    std::size_t count;
};
