#pragma once

#include <iostream>
#include <stdexcept>
#include <random>

using namespace std;

namespace list {
    template <typename T>
    struct Node {
        T _data;
        Node<T>* _prev;
        Node<T>* _next;

        Node(): _data(0), _prev(nullptr), _next(nullptr) {}
        Node(T d) : _data(d), _prev(nullptr), _next(nullptr) {}
    };

    template<typename T>
    ostream& operator<<(ostream& os, Node<T>* _node) {
        os << _node->_data << "|" << endl;
        return os;
    }

    template <typename T>
    class LinkedList {
    private:
        Node<T>* _head;
        Node<T>* _tail; 

    public:
        LinkedList() : _head(nullptr), _tail(nullptr) {}

        Node<T>* get_head() const { return _head; }
        Node<T>* get_tail() const { return _tail; }

        LinkedList(size_t n, T a, T b) : _head(nullptr), _tail(nullptr){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<T> dis(a, b);
            for (size_t i = 0; i < n; ++i) {
                push_tail(dis(gen));
            }
        }

        ~LinkedList() = default;
        //~LinkedList() {
        //    while (_head != _tail) {
        //        Node<T>* tmp = _head;
        //        _head = _head->_prev;
        //        delete tmp;
        //    }
        //    delete _tail;
        //}

        LinkedList(const LinkedList<T>& l) : _head(nullptr), _tail(nullptr){
            Node<T>* cur = l._head;
            while (cur != nullptr) {
               /* Node<T>* tmp = new Node(cur->_data);*/
                push_tail(cur->_data);
                cur = cur->_next;
            }
        }

        void swap(LinkedList<T>& l) {
            std::swap(_head, l._head);
        }

        LinkedList<T>& operator=(const LinkedList<T>& other) {
            if (other._head) {
                Node<T>* tmp = other._head;
                do {
                   /* Node<T>* cur = new Node(tmp->_data);*/
                    push_tail(tmp->_data);
                    tmp = tmp->_next;
                } while (tmp != other._head);
            }
            return *this;
        }

        void push_tail(T d) {
            Node<T>* tmp = new Node(d);
            if (_tail == nullptr) {
                _head = tmp;
                _tail = tmp;
                _tail->_next = _head;
                _head->_prev = _tail;
            }
            else {
                _tail->_next = tmp;
                tmp->_prev = _tail;
                _tail = tmp;
                _tail->_next = _head;
                _head->_prev = _tail;
            } 
        }

        void push_tail(const LinkedList& l) {
            if (l._tail == nullptr)
                throw std::invalid_argument("LinkedList::The list is empty");
            else if (_tail == nullptr) {
                _head = l._head;
                _tail = l._tail;
            }
            else {
                l._tail->_next = _head;
                _head->_prev = l._tail;
                l._head->_prev = _tail;
                _tail->_next = l._head;
                _tail = l._tail;
            }
        }

        void push_head(T d) {
            Node<T>* tmp = new Node(d);
            if (_head == nullptr) {
                _head = tmp;
                _tail = tmp;
                _tail->_next = _head;
                _head->_prev = _tail;
            }
            else {
                tmp->_next = _head;
                _head->_prev = tmp;
                _head = tmp;
                _head->_prev = _tail;
                _tail->_next = _head;
            } 
        }

        void push_head(const LinkedList& _list) {
            if (_list._head == nullptr)
                throw std::invalid_argument("LinkedList::The list is empty");
            else if (_head == nullptr) {
                _head = _list._head;
                _tail = _list._tail;
            }
            else {
                _list._tail->_next = _head;
                _head->_prev = _list._tail;
                _list._head->_prev = _tail;
                _tail->_next = _list._head;
                _head = _list._head;
            }
        }

        void pop_head() {
            if (_head == NULL)
                throw std::invalid_argument("LinkedList::The list is empty");
            else {
                Node<T>* cur = _head;
                _head = _head->_next;
                _head->_prev = _tail;
                _tail->_next = _head;
                delete cur;
            }
        }

        void pop_tail() {
            if (_tail == NULL)
                throw std::invalid_argument("LinkedList::The list is empty");
            else {
                Node<T>* cur = _tail;
                _tail = _tail->_prev;
                _head->_prev = _tail;
                _tail->_next = _head;
                delete cur;
            }
        }

        void delete_node(T d) {
            if (_head == nullptr)
                throw std::invalid_argument("LinkedList::The list is empty");
            else {
                Node<T>* cur = _head;
                do {
                    if (d == cur->_data) {
                        if (cur == _head) {
                            cur = cur->_next;
                            this->pop_head();
                        }
                        else if (cur == _tail) {
                            cur = cur->_next;
                            this->pop_tail();
                        }
                        else {
                            Node<T>* ptr = cur;
                            cur = cur->_next;
                            cur->_prev = ptr->_prev;
                            ptr->_prev->_next = cur;
                            delete ptr;
                        }
                    }
                    else {
                        cur = cur->_next;
                    }
                } while (cur != _head);
            }
        }

        T& operator[](size_t index) const {
            if (index < get_elem()) {
                Node<T>* curr = _head;
                for (size_t i = 0; i < index; ++i) {
                    curr = curr->_next;
                }
                return curr->_data;
            }
            else {
                throw std::out_of_range("Index out of range");
            }
        }

        T& operator[](size_t index) {
            if (index < get_elem()) {
                Node<T>* curr = _head;
                for (size_t i = 0; i < index; ++i) {
                    curr = curr->_next;
                }
                return curr->_data;
            }
            else {
                throw std::out_of_range("Index out of range");
            }
        }

        int get_elem() const {
            if (_head == nullptr)
                return 0;
            int len = 1;
            Node<T>* node = _head->_next;
            while (node != _head) {
                len += 1;
                node = node->_next;
            }
            return len;
        }

        void insert(T val) {
            Node<T>* newNode = new Node(val);
            if (_head == nullptr) {
                _head = newNode;
                _tail = newNode;
                _head->_next = _tail;
                _tail->_prev = _head;
            }
            else {
                Node<T>* temp = _head;
                while (temp->_next != _tail) {
                    if (temp->_data <= val && temp->_next->_data >= val) {
                        break;
                    }
                    temp = temp->_next;
                }
                if ((temp == _head && temp->_data > val) || temp->_prev->_data > val) {
                    newNode->_next = _head;
                    _head->_prev = newNode;
                    _head = newNode;
                }
                else if ((temp == _tail && temp->_data < val) || temp->_next->_data < val) {
                    newNode->_prev = _tail;
                    _tail->_next = newNode;
                    _tail = newNode;
                }
                else {
                    newNode->_next = temp->_next;
                    newNode->_prev = temp;
                    temp->_next->_prev = newNode;
                    temp->_next = newNode;
                }
            }
        }
  };

  template<typename T>
  ostream& operator<<(ostream& os, const LinkedList<T>& l) {
      os << l.get_elem() << endl;
      return os;
  }

  template<typename T>
  ostream& operator<<(ostream& os, LinkedList<T>& l) {
      Node<T>* cur = l.get_head();
      do {
          os << cur->_data << " ";
          cur = cur->_next;
      } while (cur != l.get_head());
      return os;
  }

  template<typename T>
  void removeDuplicates(LinkedList<T>& l) {
      Node<T>* current = l.get_head();
      Node<T>* index = nullptr;
      Node<T>* temp = nullptr;

      if (l.get_head() == nullptr) {
          return;
      }
      else {
          do {
              temp = current;
              index = current->_next;

              while (index != l.get_head()) {
                  if (index->_data == current->_data) {
                      temp->_next = index->_next;
                      delete index;
                      index = temp->_next;
                  }
                  else {
                      temp = index;
                      index = index->_next;
                  }
              }
              current = current->_next;
          } while (current != l.get_head());
      }
  }


  template<typename T>
  LinkedList<T> merge(LinkedList<T>& l1, LinkedList<T>& l2) {
      LinkedList<T> mergedList;
      Node<T>* temp1 = l1.get_head();
      while (temp1 != nullptr) {
          mergedList.insert(temp1->_data);
          temp1 = temp1->_next;
          if (temp1 == l1.get_head()) {
              break;
          }
      }

      Node<T>* temp2 = l2.get_head();
      while (temp2 != nullptr) {
          mergedList.insert(temp2->_data);
          temp2 = temp2->_next;
          if (temp2 == l2.get_head()) {
              break;
          }
      }

      return mergedList;
  }
 
}