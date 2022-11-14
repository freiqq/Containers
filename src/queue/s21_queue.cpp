#include "s21_queue.h"

namespace s21 {

template <class T>
s21::queue<T>::queue() {
  head_ = NULL;
  tail_ = NULL;
  count_ = 0;
}

// template <class T>
//  s21::queue<T>::queue(const std::initializer_list<value_type>& items) {}

template <class T>
queue<T>::queue(const queue& q) {
  head_ = NULL;
  tail_ = NULL;
  node_* temp_node = q.head_;
  while (temp_node) {
    this->push(temp_node->value_);
    temp_node = temp_node->next_;
  }
}

// ???
template <class T>
s21::queue<T>::queue(queue&& q) {
  head_ = q.head_;
  tail_ = q.tail_;
  q.head_ = NULL;
  q.tail_ = NULL;
}

template <class T>
s21::queue<T>::~queue() {
    node_* temp_node;
    while (head_) {
      temp_node = head_;
      head_ = head_->next_;
      --count_;
      delete temp_node;
    }
}

 template <class T>
 typename s21::queue<T> s21::queue<T>::operator=(queue&& q) {
   head_ = NULL;
   tail_ = NULL;
   node_* temp_node = q.head_;
   while (temp_node) {
     this->push(temp_node->value_);
     temp_node = temp_node->next_;
   }
   return 0;
 }

template <class T>
const T& s21::queue<T>::front() {
  // refactor: if null
  return head_->value_;
}

template <class T>
const T& s21::queue<T>::back() {
  // refactor: if null
  return tail_ ? tail_->value_ : 0;
}

template <class T>
bool s21::queue<T>::empty() {
  return !head_;
}
template <class T>
typename s21::queue<T>::size_type s21::queue<T>::size() {
  return count_;
}
template <class T>
void s21::queue<T>::push(const_reference value) {
  node_* new_node = new node_;
  if (!head_) {
    head_ = new_node;
    tail_ = head_;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
    tail_->next_ = NULL;
  }
  new_node->next_ = NULL;
  new_node->value_ = value;
  ++count_;
}
template <class T>
void s21::queue<T>::pop() {
  node_* deletable_node = tail_;
  if (head_ != tail_) {
    tail_ = tail_->prev_;
    tail_->next_ = NULL;
  } else {
    head_ = NULL;
    tail_ = NULL;
  }
  --count_;
  delete deletable_node;
}

template <class T>
void s21::queue<T>::swap(queue& other) {
  node_* temp_head = head_;
  head_ = other.head_;
  other.head_ = temp_head;
}

template <class T>
void s21::queue<T>::print() {
  node_* temp_node = head_;
  printf("queue: ");
  while (temp_node) {
    printf("%d, ", temp_node->value_);
    temp_node = temp_node->next_;
  }
}

}  // namespace s21