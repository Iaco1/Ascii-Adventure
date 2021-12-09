#include <iostream>
using namespace std;

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
	void printList(){
		Node<T> *iter=head;
		cout<<endl<<"NULL<-";
		while(iter != NULL){
			char str[24];
			iter->data.toString(str);
			printf("[%s]", str);
			iter = iter->next;
			if(iter!=NULL) cout<<"<->";
		}
		cout<<"->NULL"<<endl;
	}
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
	bool contains(Node<T> *n){
		Node<T> *iter = head;
		while(iter!=NULL){
			if(iter == n) return true;
			else iter = iter->next;
		}
		return false;
	}
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
	~LinkedList(){
		head = NULL;
		tail = NULL;
		size = 0;
	}
};
