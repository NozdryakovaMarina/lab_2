#pragma once

#include <iostream>

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
		LinkedList() {
			_head = NULL;
			_tail = NULL;
		}

		LinkedList(const LinkedList<T>& l) {
			_head = NULL;
			_tail = NULL;
			Node<T>* tmp = l._head;
			while (tmp != l._head) {
				Node<T>* node = new Node<T>(*tmp);
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
			if (_head != NULL) {
				_head->_prev = h;
				_tail->_next = h;
			}
			if (_tail == NULL) 
				_tail = h;
			h->_next = _head;
			h->_prev = _tail;
			_head = h;
		}

		void push_head(LinkedList<T>& l) {

		}

		void push_tail(Node<T>* t) {
			if (_tail != NULL) {
				_tail->_prev = t;
				_head->_next = t;
			}
			if (_head == NULL)
				_head = t;
			t->_prev = _head;
			t->_next = _tail;
			_tail = t;
		}

		void push_tail(LinkedList<T>& l) {

		}

		void pop_head() {
			if (_head == NULL) return;

			Node<T>* tmp = _head->_next;
			if (tmp != NULL)
				tmp->_prev = NULL;
			else
				_tail = NULL;

			delete _head;
			_head = tmp;
		}

		void pop_tail() {
			if (_tail == NULL) return;

			Node<T>* tmp = _tail->_prev;
			if (tmp != NULL)
				tmp->_next = NULL;
			else
				_head = NULL;

			delete _tail;
			_tail = tmp;
		}

		void delete_node(T val) {
			Node<T> tmp = _head;

		}

		Node<T>* operator[](int ind) {
			Node<T>* tmp = _head;
			for (int i = 0; i < ind; i++) {
				if (tmp == NULL)
					return tmp;
				tmp = tmp->next;
				i++;
			}
			return tmp;
		}
	};
}