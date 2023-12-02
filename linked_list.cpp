#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

namespace list {
	template<typename T>
	struct Node {
		T _val;
		Node<T>* _next;
		Node<T>* _prev;
		Node() : _val(0), _next(nullptr), _prev(nullptr) {}
		Node(T val, Node<T>* next, Node<T>* prev): _val(val), _next(next), _prev(prev) {}
	};

	template<typename T>
	class LinkedList {
		Node<T>* _head;
		Node<T>* _tail;
	public:
		LinkedList(): _head(nullptr), _tail(nullptr) {}

		LinkedList(const LinkedList<T>& l) {
			_head = nullptr;
			_tail = nullptr;
			Node<T>* tmp = l._head;
			while (tmp != l._head) {
				Node<T>* node = new Node<T>(tmp->_val);
				push_tail(node);
				tmp = tmp->_next;
			}
		}

		void swap(LinkedList<T>& l) {
			std::swap(_head, l._head);
			std::swap(_tail, l._tail);
		}

		LinkedList<T>& operator=(LinkedList<T> l) {
			swap(l);
			return *this;
		}

		~LinkedList() {
			while (_head != _tail) {
				Node<T>* tmp = _head;
				_head = _head->prev;
				delete tmp;
			}
			delete _tail;
		}

		void push_head(Node<T>* h) {
			if (_head != nullptr) {
				_head->_prev = h;
				_tail->_next = h;
			}
			if (_head == nullptr) 
				_tail = h;
			h->_next = _head;
			h->_prev = _tail;
			_head = h;
		}

		void push_head(LinkedList<T>& l) {
			if (l._head == nullptr)
				throw invalid_argument("The list is empty.");
			if (_head == nullptr) {
				_head = l._head;
				_tail = l._tail;
			}
			   
		}

		void push_tail(Node<T>* t) {
			if (_tail != nullptr) {
				_tail->_prev = t;
				_head->_next = t;
			}
			if (_tail == nullptr)
				_head = t;
			t->_prev = _head;
			t->_next = _tail;
			_tail = t;
		}

		void push_tail(LinkedList<T>& l) {
			if (l.pop_head == nullptr)
				throw invalid_argument("The list is empty.");
			if (_tail == nullptr) {
				_head = l._head;
				_tail = l._tail;
			}

		}

		void pop_head() {
			if (_head == nullptr)
				throw invalid_argument("The list is empty.");

			Node<T>* tmp = _head->_next;
			_head->_prev = _tail;
			_tail->_next = _head;
			delete tmp;
		}

		void pop_tail() {
			if (_tail == nullptr)
				throw invalid_argument("The list is empty.");

			Node<T>* tmp = _tail->_prev;
			_head->_prev = _tail;
			_tail->_next = _head;
			delete tmp;
		}

		void delete_node(T val) {
			Node<T> tmp = _head;

		}

		int get_size(Node<T>* h) const{
			int count = 0;
			Node<T>* tmp = h;
			while (tmp != h) {
				count++;
				tmp = tmp->_next;
			}
			return count;
		}
		
		Node<T>* operator[](int ind) const {
			if (ind < 0 || ind > = get_size(_head))
				throw std::out_of_range("Index is out of range.");
			else {
				Node<T>* tmp = _head;
				for (int i = 0; i < ind; i++)
					tmp = tmp->next;
				return tmp;
			}
		}
	};
}