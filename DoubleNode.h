#pragma once

template <typename T>
class DoubleNode
{
public:
    T data;
    DoubleNode<T>* next;
    DoubleNode<T>* prev;

    DoubleNode() : data(), next(nullptr), prev(nullptr) {}
    explicit DoubleNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};
