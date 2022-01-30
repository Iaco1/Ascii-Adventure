#pragma once
#include <iostream>
#include <cstdarg>
using namespace std;

/*
doubly-linked list data structure class
*/

template <class T>
class Node{
	public:
	T data;
	Node *next;
	Node *prev;
	Node(){
		data = T();
		next = NULL;
		prev = NULL;
	}
	Node(T data){
		this->data = data;
		prev = NULL;
		next = NULL;
	}
};

template <class T>
class LinkedList{
	private:
	Node<T> *head;
	Node<T> *tail;
	int size;
	
	public:
	LinkedList(){
		head = NULL;
		tail = NULL;
		size = 0;
	}
	Node<T>* getHead(){ return head; }
	Node<T>* getTail(){ return tail; }
	
	//inserts node in the head
	void pushHead(Node<T> *n){
		if(head == NULL) {
			head = n;
			tail = n;
		}else if(head == tail){
			head = n;	
			head->next = tail;
			tail->prev = head;
		}else{
			n->next = head;
			head->prev = n;
			head = n;
		}
		size++;
	}
	
	//inserts node in the tail
	void pushTail(Node<T> *n){
		if(tail==NULL){
			head = n;
			tail = n;
		}else if(head == tail){
			head->next = n;
			n->prev = head;
			tail = n;
		}else{
			tail->next = n;
			n->prev = tail;
			tail = n;
		}
		size++;
	}
	
	//inserts node at index i
	void pushIndex(Node<T> *n, int i){
		Node<T> *iter = head;
		if(i==0) pushHead(n);
		else if(i == size) pushTail(n);
		else if(i<size && i>0){
			while(i>0){
				iter = iter->next;
				i--;
			}
			Node<T> *previous = iter->prev;
			previous->next = n;
			n->prev = previous;
			n->next = iter;
			iter->prev = n;
			size++;
		}
	}
	
	//deletes the node in head
	void popHead(){
		if(size>1){
			head = head->next;
			head->prev = NULL;
			size--;
		}else if(size == 1) {
			head = NULL;
			tail = NULL;
			size--;
		}
	}
	
	// deletes the node in tail 
	void popTail(){
		if(size>1){
			tail = tail->prev;
			tail->next = NULL;
			size--;
		}else if(size == 1) {
			tail = NULL;
			head = NULL;
			size--;
		}
	}
	
	//deletes the node at index i
	void popIndex(int i){
		Node<T> *iter = head;
		if(size>0){
			if(i==0) popHead();
			else if(i==size-1) popTail();
			else if(i>0 && i<size-1){
				while(i>0){
					iter = iter->next;
					i--;
				}
				Node<T> *iter_prev = iter->prev;
				Node<T> *iter_next = iter->next;
				iter_prev->next = iter_next;
				iter_next->prev = iter_prev;
				iter->prev = NULL;
				iter->next = NULL;
				size--;
			}
		}
	}
	
	//returns the node at index i
	Node<T>* getNodeAt(int i){
		if((i>0 || i==0) && i<size){
			if(i==0) return head;
			else if(i == size-1) return tail;
			else{
				Node<T> *iter = head;
				while(i>0){
					iter = iter->next;
					i--;
				}
				return iter;
			}
		}else return NULL;
	}
	
	//returns whether the list contains node n or not
	bool contains(Node<T> *n){
		Node<T> *iter = head;
		while(iter!=NULL){
			if(iter == n) return true;
			else iter = iter->next;
		}
		return false;
	}
	
	//returns whether the list contains any nodes that have that matches at least one of the argn no. of arguments 
	bool containsAnyData(int argn, ...){
		va_list list;
  		va_start(list, argn);
		
		for(int i=0; i<argn; i++){
			Node<T> *iter = head;
			while(iter!=NULL){
				if(iter->data == va_arg(list, T)) {
					va_end(list);
					return true;
				}
				else iter = iter->next;
			}
		}
		return false;
	}
	
	//returns the index for node n
	int getIndex(Node<T> *n){
		int i=0;
		if(contains(n)){
			Node<T> *iter = head;
			while(iter!=NULL){
				if(iter == n) return i;
				else{
					i++;
					iter = iter->next;
				}
			}
		}else return -1;
	}

	int getSize(){ return size; }
	
	T& operator[](int index) {
		if (index >= size || index < 0) {
			cout << "Error: index out of bounds" << endl;
			exit(EXIT_FAILURE);
		}
		Node<T>* iter;
		if (index + 1 <= size / 2) {
			iter = head;
			for (int i = 0; i < index; i++, iter = iter->next);
		}
		else {
			iter = tail;
			for (int i = size - 1; i > index; i--, iter = iter->prev);
		}
		return iter->data;
	}
	
	bool isEmpty(){
		return head == NULL;
	}

	//deltes the node
	void popNode(Node<T> *n){
		if(n == head) popHead();
		else if(n == tail) popTail();
		else{
			Node<T>* iter = head;
			while(iter!=NULL){
				if(iter == n){
					Node<T>* iter_prev = iter->prev;
					Node<T>* iter_next = iter->next;
					iter_prev->next = iter_next;
					iter_next->prev = iter_prev;
					n->prev = NULL;
					n->next = NULL;
					delete n;
					size--;
					break;
				}
				iter = iter->next;
			}
		}
	}	
	
	//appends the nodes of ll to this->tail
	void appendList(LinkedList<T> ll){
		Node<T> *n = ll.getHead();
		while(n!=NULL){
			pushTail(n);
			n = n->next;
		}
	}
	
	~LinkedList(){
		head = NULL;
		tail = NULL;
		size = 0;
	}
};
