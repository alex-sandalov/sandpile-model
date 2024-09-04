#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <iostream>

struct Pixel {
    int16_t x_coord = 0;
    int16_t y_coord = 0;
    uint64_t sandbox = 0;
    
    Pixel(int16_t x, int16_t y, uint64_t s);

    Pixel(int16_t x, int16_t y);
};

struct DoubleLinkedList {
    DoubleLinkedList* next;
    DoubleLinkedList* previous;
    Pixel pixel;

    DoubleLinkedList(const Pixel& value, DoubleLinkedList* n, DoubleLinkedList* p);
};

class Queue {
private:
    DoubleLinkedList *head;
    DoubleLinkedList *tail;

public:
    Queue();
    
    Pixel pop();
    
    void push(Pixel value);

    bool is_empty() const;
    
    int64_t size() const;

    ~Queue();
};