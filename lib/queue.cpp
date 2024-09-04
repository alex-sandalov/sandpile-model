#include "queue.h"
#include <cstddef>
#include <cstdint>

Pixel::Pixel(int16_t x, int16_t y, uint64_t s) 
    : x_coord(x), y_coord(y), sandbox(s) {}

Pixel::Pixel(int16_t x, int16_t y) 
    : x_coord(x), y_coord(y), sandbox(0) {}

DoubleLinkedList::DoubleLinkedList(const Pixel& value, DoubleLinkedList* n, DoubleLinkedList* p=nullptr) 
    : pixel(value), next(n), previous(p) {}

Queue::Queue() 
    : head(nullptr), tail(nullptr) {}

Pixel Queue::pop() {
    Pixel return_pop = tail->pixel;
    DoubleLinkedList* current = tail->previous;
    delete tail;
    tail = current;
    return return_pop;    
}

void Queue::push(Pixel value) {
    DoubleLinkedList* current = new DoubleLinkedList(value, head);
    if (!tail) {
        head = current;
        tail = head;
    } else {
        head->previous = current;
        head = current;
    }
}

bool Queue::is_empty() const {
    return tail == nullptr;
}

int64_t Queue::size() const {
    if (Queue::is_empty()) {
        return 0;
    }
    DoubleLinkedList* current = tail;
    int64_t lenght = 1;
    while (current) {
        ++lenght;
        current = current->previous;
    }
    return lenght;
}

Queue::~Queue() {
    while (tail) {
        pop();
    }
}