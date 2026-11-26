#pragma once

#include <cstddef>

template <typename T>
class List
{
public:
    virtual ~List() = default;

    virtual void pushFront(const T& value) = 0;
    virtual void pushBack(const T& value) = 0;
    virtual void insertAt(std::size_t index, const T& value) = 0;

    virtual bool remove(const T& value) = 0;
    virtual bool removeAt(std::size_t index) = 0;
    virtual void clear() = 0;

    virtual T& at(std::size_t index) = 0;
    virtual const T& at(std::size_t index) const = 0;
    virtual bool contains(const T& value) const = 0;

    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;
};
