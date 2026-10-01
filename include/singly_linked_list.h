#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
struct SNode {
    T value;
    SNode* next;

    explicit SNode(const T& v, SNode* n = nullptr) : value(v), next(n) {}
};

template <typename T>
class SLinkedList {
public:
    SLinkedList();
    ~SLinkedList();
    SLinkedList(const SLinkedList& other);
    SLinkedList& operator=(const SLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    bool pop_front();
    bool pop_back();

    T& front();
    const T& front() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    bool contains(const T& value) const;
    std::vector<T> to_vector() const;
    void clear();

private:
    SNode<T>* head_;
    std::size_t size_;
};

template <typename T>
SLinkedList<T>::SLinkedList() : head_(nullptr), size_(0) {}

template <typename T>
SLinkedList<T>::~SLinkedList() {
//TODO: Implement the destructor for the SLinkedList class
    clear();
}

template <typename T>
SLinkedList<T>::SLinkedList(const SLinkedList& other) : head_(nullptr), size_(other.size_) {
//TODO: Implement the copy constructor for the SLinkedList class
    if (!other.empty()) {
        SNode<T>* prev = new SNode<T>(other.head_->value, nullptr); //completely distinct new head
        head_ = prev;
        for (SNode<T>* current = other.head_->next; current != nullptr; current = current->next) {
            SNode<T>* n = new SNode<T>(current->value, nullptr); //create distinct copy of nodes
            prev->next = n; //link previous
            prev = n; //move 
        }
    }
}

template <typename T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& other) {
//TODO: Implement the assignment operator for the SLinkedList class
    if (this != &other) { //self assignment protection
        clear(); //empty existing memory
        if (!other.empty()) {
            SNode<T>* prev = new SNode<T>(other.head_->value, nullptr);
            head_ = prev;
            for (SNode<T>* current = other.head_->next; current != nullptr; current = current->next) {
                SNode<T>* n = new SNode<T>(current->value, nullptr);
                prev->next = n;
                prev = n;
            }
        }
        size_ = other.size_;
    }
    return *this;
}

template <typename T>
void SLinkedList<T>::push_front(const T& value) {
// TODO: Implement the push_front function for the SLinkedList class
    SNode<T>* headNode = new SNode<T>(value, head_); //new head, next node is current head
    head_ = headNode; //update list head
    size_++;
}

template <typename T>
void SLinkedList<T>::push_back(const T& value) {
// TODO: Implement the push_back function for the SLinkedList class
    SNode<T>* tailNode = new SNode<T>(value, nullptr); //new tail, needs link to end 
    SNode<T>* oldTail = head_;
    while (oldTail->next != nullptr) { //find old tail
        oldTail = oldTail->next;
    }
    oldTail->next = tailNode; //link to new tail
    size_++;
}

template <typename T>
bool SLinkedList<T>::pop_front() {
// TODO: Implement the pop_front function for the SLinkedList class
    if (empty()) { return false; } //exit early
    SNode<T>* forDelete = head_; //save location head
    head_ = head_->next; // change head 
    delete forDelete; //delete saved head, not actual head
    size_--;
    return true;
}

template <typename T>
bool SLinkedList<T>::pop_back() {
// TODO: Implement the pop_back function for the SLinkedList class
    if (empty()) { return false; } //exit early
    SNode<T>* newTail = head_;
    while (newTail->next->next != nullptr) { //stop before last node
        newTail = newTail->next;
    }
    SNode<T>* forDelete = newTail->next;
    newTail->next = nullptr; //unpoint from existing tail, cannot do if nonexistent
    delete forDelete; //delete saved end 
    size_--;
    return true;
}

template <typename T>
T& SLinkedList<T>::front() {
// TODO: Implement the front function for the SLinkedList class
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    }
    return head_->value;
}

template <typename T>
const T& SLinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    }
    return head_->value;
}

template <typename T>
std::size_t SLinkedList<T>::size() const noexcept {
// TODO: Implement the size function for the SLinkedList class
    return size_;
}

template <typename T>
bool SLinkedList<T>::empty() const noexcept {
// TODO: Implement the empty function for the SLinkedList class
    return (head_ == nullptr) ? true : false;
}

template <typename T>
bool SLinkedList<T>::contains(const T& value) const {
// TODO: Implement the contains function for the SLinkedList class
    for (SNode<T>* current = head_; current != nullptr; current = current->next) {
        if (current->value == value) { return true; }
    }
    return false;
}

template <typename T>
std::vector<T> SLinkedList<T>::to_vector() const {
    std::vector<T> values;
    values.reserve(size_);
    for (SNode<T>* current = head_; current != nullptr; current = current->next) {
        values.push_back(current->value);
    }
    return values;
}

template <typename T>
void SLinkedList<T>::clear() {
//TODO: Implement the clear function for the SLinkedList class
    while (pop_front()) { continue; } //as bool function, should return false when empty
}
