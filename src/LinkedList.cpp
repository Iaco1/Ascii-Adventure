#pragma once
#include <cstddef>
#include <iostream>
#include <cstring>
#include <typeinfo>
#include "LinkedList.hpp"

template<class T>
LinkedList<T>::LinkedList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

template<class T>
void LinkedList<T>::pushHead(T val) {
	size++;
	node<T>* temp = new node<T>;
	temp->next = head;
	temp->prev = NULL;
	temp->data = val;
	if (head != NULL)
		head->prev = temp;
	head = temp;
	if (tail == NULL)
		tail = head;
}

template<class T>
void LinkedList<T>::pushTail(T val) {
	size++;
	node<T>* temp = new node<T>;
	temp->next = NULL;
	temp->prev = tail;
	temp->data = val;
	if (tail != NULL)
		tail->next = temp;
	tail = temp;
	if (head == NULL)
		head = tail;
}

template<class T>
node<T>* LinkedList<T>::popHead() {
	node<T>* temp = head;
	if (size == 1) {
		size--;
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) {
		size--;
		head = head->next;
		head->prev = NULL;
	}
	return temp;
}

template<class T>
node<T>* LinkedList<T>::popTail() {
	node<T>* temp = tail;
	if (size == 1) {
		size--;
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) {
		size--;
		tail = tail->prev;
		tail->next = NULL;
	}
	return temp;
}

template <class T>
void LinkedList<T>::remove(node<T>* n) {
	if (n->prev == NULL)
		head = n->next;
	else
		(n->prev)->next = n->next;
	if (n->next == NULL)
		tail = n->prev;
	else
		(n->next)->prev = n->prev;
	size--;
	delete n;
}

template <class T>
void LinkedList<T>::remove(T val) {
	if (size <= 0) return;
	if (val == head->data) {
		delete popHead();
		return;
	}
	if (size == 1) return;
	node<T> iter = head->next;
	while (iter != tail) {
		if (val == iter->data) {
			(iter->prev)->next = iter->next;
			(iter->next)->prev = iter->prev;
			delete iter;
			size--;
			return;
		}
		iter = iter->next;
	}
	if (val == tail->data) {
		delete popTail();
		return;
	}
}

template <class T>
void LinkedList<T>::reverse() {
	node<T>* temp = head;
	head = tail;
	tail = temp;
	node<T> iter = tail;
	while (iter != NULL) {
		temp = iter->next;
		iter->next = iter->prev;
		iter->prev = temp;
		temp = temp->prev;
	}
}

template<class T>
T& LinkedList<T>::operator[](int index) {
	node<T>* iter;
	if (index + 1 <= size / 2) {
		iter = head;
		int i = 0;
		while (i < index) {
			iter = iter->next;
			i++;
		}
	}
	else {
		iter = tail;
		int i = size - 1;
		while (i > index) {
			iter = iter->prev;
			i--;
		}
	}
	return iter->data;
}

template <class T>
void LinkedList<T>::printList() {
	using namespace std;
	if (typeid(T).name() == typeid(int).name()) {
		node<T>* iter = head;
		cout << endl << "[ prev<->(data, index)<->next ]" << endl << "NULL<->";
		for (int i = 0; i < size; i++, iter = iter->next)
			cout << "(" << iter->data << ", " << i << ")<->";
		cout << "NULL" << endl;
	}
	else
		printf("\n%s UNSUPPORTED_TYPE\n", typeid(T).name());
}

template <class T>
int LinkedList<T>::getSize() { return size; }

template <class T>
void LinkedList<T>::randGenInt(int size, int lowBound, int upBound) {
	if (typeid(T).name() == typeid(int).name()) {
		while (size-- > 0)
			pushTail(rand() % upBound + lowBound);
	}
}