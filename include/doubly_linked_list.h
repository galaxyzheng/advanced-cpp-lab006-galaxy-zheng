#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
struct DNode {
    T value;
    DNode* prev;
    DNode* next;

    explicit DNode(const T& v, DNode* p = nullptr, DNode* n = nullptr)
        : value(v), prev(p), next(n) {}
};

template <typename T>
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    DLinkedList(const DLinkedList& other);
    DLinkedList& operator=(const DLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    bool pop_front();
    bool pop_back();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    bool contains(const T& value) const;
    std::vector<T> to_vector() const;
    void clear();

private:
    DNode<T>* header_;
    DNode<T>* trailer_;
    std::size_t size_;
};

template <typename T>
DLinkedList<T>::DLinkedList() : size_(0) {
    header_ = new DNode<T>(T(), nullptr, nullptr);
    trailer_ = new DNode<T>(T(), nullptr, nullptr);
    header_->next = trailer_;
    trailer_->prev = header_;
}

//TODO: Implement the destructor, copy constructor, assignment operator, and other member functions for the DLinkedList class.
template <typename T>
DLinkedList<T>::~DLinkedList() {
    clear();
    delete header_; //sentinels arent part of clear but are allocated with new
    delete trailer_;
}

//TODO: Implement the copy constructor for the DLinkedList class.
template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& other) : size_(other.size_) {
    DNode<T>* prev = new DNode<T>(other.header_->value, nullptr, nullptr); //new header (completely distinct from old header)
    header_ = prev;
    for (DNode<T>* current = other.header_->next; current->next != nullptr; current = current->next) { //every node after until trailer
            DNode<T>* n = new DNode<T>(current->value, prev, nullptr); //completely new node, linked to newly created prev node
            prev->next = n; //link prev to now created new node
            prev = n; //move to next
    }
    trailer_ = new DNode<T>(other.trailer_->value, prev, nullptr);
}

// TODO: Implement the assignment operator for the DLinkedList class.
template <typename T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList& other) {
    if (this != &other) { //self assignment protection
        clear(); delete header_; delete trailer_; //empty any existing
        DNode<T>* prev = new DNode<T>(other.header_->value, nullptr, nullptr);
        header_ = prev;
        for (DNode<T>* current = other.header_->next; current->next != nullptr; current = current->next) {
                DNode<T>* n = new DNode<T>(current->value, prev, nullptr);
                prev->next = n;
                prev = n;
        }
        trailer_ = new DNode<T>(other.trailer_->value, prev, nullptr);
        size_ = other.size_; 
    }
    return *this;
}

//TODO: Implement the push_front function for the DLinkedList class.
template <typename T>
void DLinkedList<T>::push_front(const T& value) {
    DNode<T>*& oldFront = header_->next;
    DNode<T>* n = new DNode<T>(value, header_, oldFront); //new front between header and front
    oldFront->prev = n; //couple adjacent nodes
    header_->next = n;
    size_ ++;
}

//TODO: Implement the push_back function for the DLinkedList class.
template <typename T>
void DLinkedList<T>::push_back(const T& value) {
    DNode<T>*& oldBack = trailer_->prev;
    DNode<T>* n = new DNode<T>(value, oldBack, trailer_); //new last between last and trailer
    oldBack->next = n; //couple adjacent nodes
    trailer_->prev = n;
    size_ ++;
}


//TODO: Implement the pop_front function for the DLinkedList class.
template <typename T>
bool DLinkedList<T>::pop_front() {
    if (empty()) {return false;} //early exit
    DNode<T>*& newFront = header_->next->next; //save new front
    DNode<T>*& forDelete = newFront->prev; 
    header_->next = newFront; //undock old from header
    delete forDelete;
    newFront->prev = header_; //dock new front to header
    size_ --;
    return true;
}

//TODO: Implement the pop_back function for the DLinkedList class.
template <typename T>
bool DLinkedList<T>::pop_back() {
    if (empty()) {return false;} //exit if nothing to pop
    DNode<T>*& newBack = trailer_->prev->prev; //save location before last 
    DNode<T>*& forDelete = newBack->next; //save location of last
    trailer_->prev = newBack; //undock old from trailer
    delete forDelete; 
    newBack->next = trailer_; //dock new last to trailer
    size_ --;
    return true;
}

//TODO: Implement the front function for the DLinkedList class
template <typename T>
T& DLinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    } return header_->value;
}

template <typename T>
const T& DLinkedList<T>::front() const {
//TODO: Implement the const version of the front function for the DLinkedList class
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    } return header_->value;
}

template <typename T>
T& DLinkedList<T>::back() {
//TODO: Implement the back function for the DLinkedList class
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    } return trailer_->value;
}

template <typename T>
const T& DLinkedList<T>::back() const {
//TODO: Implement the const version of the back function for the DLinkedList class
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    } return trailer_->value;
}

template <typename T>
std::size_t DLinkedList<T>::size() const noexcept {
//TODO: Implement the size function for the DLinkedList class
    return size_; 
}

template <typename T>
bool DLinkedList<T>::empty() const noexcept {
//TODO: Implement the empty function for the DLinkedList class
    return (header_->next == trailer_) ? true : false; //no nodes between sentinels?
}

template <typename T>
bool DLinkedList<T>::contains(const T& value) const {
//TODO: Implement the contains function for the DLinkedList class
    if (empty()) {return false;} //make sure at least 1 value before loop
    for (DNode<T>* current = header_->next; current != trailer_; current = current->next) {
        if (current->value == value) { return true; }
    } return false;
}

template <typename T>
std::vector<T> DLinkedList<T>::to_vector() const {
// TODO: Implement the to_vector function for the DLinkedList class
    std::vector<T> values;
    values.reserve(size_);
    if (empty()) {return values;} //make sure at least 1 value before loop
    for (DNode<T>* current = header_->next; current != trailer_; current = current->next) {
        values.push_back(current->value);
    } return values;
}

template <typename T>
void DLinkedList<T>::clear() {
// TDOO: Implement the clear function for the DLinkedList class
    while (pop_front()) {continue;}
}
