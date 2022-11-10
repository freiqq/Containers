// #include <initializer_list>
#include "s21_list.h"

#include "cstring"

// namespace s21 {
int main() {
  list<int> a;
  list<int> b;

  //  b.push_back(1000);
  //  b.push_back(2000);

  a.push_back(1);
  a.push_back(1);
  a.push_back(1);
  a.push_back(1);
  a.push_back(1);
  a.push_back(2);
  a.push_back(2);
  a.push_back(2);
  a.push_back(2);
  a.push_back(2);
  a.push_back(2);
  a.push_back(4);
  a.push_back(4);
  a.push_back(4);
  a.push_back(4);
  a.push_back(4);
  a.push_back(5);
  //  a.push_back(6);
  printf("%d\n", *a.begin());
  printf("%d\n", *a.end());
  //  a.sort();
  //  b.sort();
  //  a.merge(b);
  a.print_list();
  a.unique();
  list<int>::iterator itr = a.begin();
  itr++;
  itr++;
  printf("%d\n", *itr);
  //  a.reverse();
  //  a.erase(itr);
  a.iterator_insert(itr, 0);
  a.print_list();

  return 0;
}
// CONSTRUCTORS
// =================================================================
template <class T>
list<T>::list() {
  head_ = NULL;
  tail_ = NULL;
  count_ = 0;
}

template <class T>
list<T>::list(size_type n) {
  head_ = NULL;
  tail_ = NULL;
  count_ = 0;
  for (size_type i = 0; i < n; i++) {
    push_back(T());
  }
}

// template <class T>
// list<T>::list(std::initializer_list<value_type> const &items){}

template <class T>
list<T>::list(const list &l) {
  head_ = NULL;
  tail_ = NULL;
  node *temp_node = l.head_;
  while (temp_node) {
    this->push_back(temp_node->data_);
    temp_node = temp_node->next_;
  }
}

template <class T>
list<T>::list(list &&l) {
  //  head_ = NULL;
  //  tail_ = NULL;
  //  node *temp_node = l.head_;
  //  while (temp_node) {
  //    this->push_back(temp_node->data_);
  //    temp_node = temp_node->next_;
  //  }
}

template <class T>
list<T>::~list() {
  clear();
}

// template <class T>
// int list<T>::operator=(list &&l) { return 0; }
// memset
// ELEMENT ACCESS
// =================================================================

template <class T>
const T &list<T>::front() {
  return head_->data_;
}

template <class T>
const T &list<T>::back() {
  return tail_->data_;
}

// ITERATORS

template <class T>
typename list<T>::iterator list<T>::begin() {
  list<T>::iterator iterator;
  iterator = *head_;
  iterator.value_ = head_->data_;
  return iterator;
}

template <class T>
typename list<T>::iterator list<T>::end() {
  list<T>::iterator iterator;
  iterator.value_ = count_;
  return iterator;
}

// INFORMATION =================================================================
template <class T>
bool list<T>::empty() {
  return !head_;
}

template <class T>
size_t list<T>::size() {
  return count_;
}

template <class T>
size_t list<T>::max_size() {
  return 0;
}

// METHODS TO MODIFY
// =================================================================
template <class T>
void list<T>::clear() {
  node *temp_node;
  while (head_) {
    temp_node = head_;
    head_ = head_->next_;
    delete temp_node;
    count_--;
  }
  //  head_ = NULL;
}

template <class T>
typename list<T>::iterator list<T>::iterator_insert(iterator pos, const_reference value) {
  node *new_node = new node;
  new_node->data_ = value;
  new_node->next_ = pos.node_;
  if(pos.node_->prev_) {
    new_node->prev_ = pos.node_->prev_;
    pos.node_->prev_->next_ = new_node;
  } else {
    head_ = new_node;
    new_node->prev_ = NULL;
  }
//  if(!pos.node_->next_) {
//    new_node->next_ = NULL;
//  }
  pos.node_->prev_ = new_node;
  return pos;
}

template <class T>
void list<T>::erase(iterator pos) {
  if (pos.node_->prev_) {
    pos.node_->prev_->next_ = pos.node_->next_;
  } else {
    head_ = pos.node_->next_;
  }
  if (pos.node_->next_) {
    pos.node_->next_->prev_ = pos.node_->prev_;
  } else {
    tail_ = pos.node_->prev_;
  }
  delete pos.node_;
}

template <class T>
void list<T>::push_back(const_reference value) {
  node *new_node = new node;
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
  new_node->data_ = value;
  count_++;
}

template <class T>
void list<T>::pop_back() {
  node *temp_node = tail_;
  if (head_ != tail_) {
    tail_ = tail_->prev_;
    tail_->next_ = NULL;
  }
  delete temp_node;
  count_--;
}

template <class T>
void list<T>::push_front(const_reference value) {
  node *new_node = new node;
  if (!head_) {
    head_ = new_node;
    tail_ = head_;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
  }

  new_node->prev_ = NULL;
  new_node->data_ = value;
  count_++;
}

template <class T>
void list<T>::pop_front() {
  node *temp_node = head_;
  if (head_ != tail_) {
    head_ = head_->next_;
    head_->prev_ = NULL;
  } else {
    head_ = NULL;
    tail_ = NULL;
  }
  delete temp_node;
  count_--;
}

template <class T>
void list<T>::swap(list &other) {
  node *temp_node = head_;
  size_type count = count_;
  head_ = other.head_;
  count_ = other.count_;
  other.head_ = temp_node;
  other.count_ = count;
}

template <class T>
void list<T>::merge(list &other) {
  if (tail_->data_ < other.head_->data_) {
    tail_->next_ = other.head_;
    tail_ = other.tail_;
  } else {
    other.tail_->next_ = head_;
    head_->prev_ = other.tail_;
    head_ = other.head_;
  }
  count_ += other.count_;
  other.head_ = NULL;
}

template <class T>
void list<T>::splice(const_iterator pos, list &other) {}

template <class T>
void list<T>::reverse() {
  node *temp_tail = tail_;
  node *temp_head = head_;
  value_type temp_value;
  while (temp_head != temp_tail && temp_head->prev_ != temp_tail) {
    temp_value = temp_head->data_;
    temp_head->data_ = temp_tail->data_;
    temp_tail->data_ = temp_value;
    temp_tail = temp_tail->prev_;
    temp_head = temp_head->next_;
  }
}

template <class T>
void list<T>::unique() {
  node *temp_head = head_;
  node *node_for_delete;
  while (temp_head) {
    if (temp_head->next_ && temp_head->data_ == temp_head->next_->data_) {
      node_for_delete = temp_head->next_;
      temp_head->next_ = temp_head->next_->next_;
      temp_head->next_->prev_ = temp_head;
      delete node_for_delete;
    } else {
      temp_head = temp_head->next_;
    }
  }
}
template <class T>
void list<T>::sort() {
  value_type temp_value;
  node *temp_head = head_;
  while (temp_head) {
    node *temp_node = temp_head;
    while (temp_node->prev_ && temp_node->prev_->data_ > temp_node->data_) {
      temp_value = temp_node->prev_->data_;
      temp_node->prev_->data_ = temp_node->data_;
      temp_node->data_ = temp_value;
      temp_node = temp_node->prev_;
    }
    temp_head = temp_head->next_;
  }
}

// additional temp methods
// =================================================================
template <class T>
void list<T>::print_list() {
  //  printf("%ld\n", count_);
  printf("__________________________\n");
  node *temp_node = head_;
  while (temp_node) {
    printf("data: %d\n", temp_node->data_);
    temp_node = temp_node->next_;
  }
}

template <class T>
void list<T>::itr() {
  list<T>::iterator iterator;
  iterator = this->end();
  //  ++iterator;
  //  iterator++;
  //  iterator--;
  //  --iterator;
  //  T iterator = this->head_;
  printf("%d", *iterator);
}

template <class T>
list<T>::ListIterator::ListIterator() {
  node_ = NULL;
}

/////////////////

template <class T>
void list<T>::ListIterator::operator=(node &node) {
  node_ = &node;
  value_ = node.data_;
}

template <class T>
typename list<T>::value_type &list<T>::ListIterator::operator*() {
  return value_;
}

template <class T>
void list<T>::ListIterator::operator++(value_type) {
  node_ = node_->next_;
  if (node_) {
    value_ = node_->data_;
  }
}

template <class T>
void list<T>::ListIterator::operator++() {
  node_ = node_->next_;
  value_ = node_->data_;
}

template <class T>
void list<T>::ListIterator::operator--(value_type) {
  node_ = node_->prev_;
  value_ = node_->data_;
}

template <class T>
void list<T>::ListIterator::operator--() {
  node_ = node_->prev_;
  value_ = node_->data_;
}
template <class T>

bool list<T>::ListIterator::operator!=(list<T>::ListIterator iterator) {
  return node_ != iterator.node_;
}

//};  // namespace s21
