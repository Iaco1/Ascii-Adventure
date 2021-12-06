#include <iostream>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node* next;
	Node* prev;
	Node() {
		data = T();
		next = NULL;
		prev = NULL;
	}
	Node(T d) {
		data = d;
		prev = NULL;
		next = NULL;
	}
	~Node() {
		if (prev != NULL) { prev->next = next; }
		if (next != NULL) { next->prev = prev; }
		delete data;
	}
};

template <class T>
class LinkedList {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	LinkedList() {
		head = NULL;
		tail = NULL;
		size = 0;
	}
	Node<T>* getHead() { return head; }

	Node<T>* getTail() { return tail; }

	void pushHead(Node<T>* n) {
		n->next = head;
		head = n;
		if (n->next != NULL) n->next->prev = n;
		else tail = head;
		size++;
	}

	void pushTail(Node<T>* n) {
		n->prev = tail;
		tail = n;
		if (n->prev != NULL) n->prev->next = n;
		else head = tail;
		size++;
	}

	void pushIndex(Node<T>* n, int i) {
		if (i == 0) pushHead(n);
		else if (i == size) pushTail(n);
		else if (i < size && i > 0) {
			Node<T>* iter = head;
			while (i > 0) {
				iter = iter->next;
				i--;
			}
			n->next = iter;
			n->prev = iter->prev;
			iter->prev = n;
			n->prev->next = n;
			size++;
		}
	}

	void printList() {
		Node<T>* iter = head;
		cout << endl << "NULL<-";
		while (iter != NULL) {
			char str[24];
			iter->data.toString(str);
			printf("[%s]", str);
			iter = iter->next;
			if (iter != NULL) cout << "<->";
		}
		cout << "->NULL" << endl;
	}

	Node<T>* popHead(bool cleanup = true) {
		size--;
		Node<T>* tmp = head;
		head = head->next;
		if (head != NULL) head->prev = NULL;
		else tail = NULL;
		if (cleanup) {
			delete n;
			return NULL;
		}
		else {
			tmp->prev = NULL;
			tmp->next = NULL;
			return tmp;
		}
	}

	Node<T>* popTail(bool cleanup = true) {
		size--;
		Node<T>* tmp = tail;
		tail = tail->prev;
		if (tail != NULL) tail->next = NULL;
		else head = NULL;
		if (cleanup) {
			delete n;
			return NULL;
		}
		else {
			tmp->prev = NULL;
			tmp->next = NULL;
			return tmp;
		}
	}

	Node<T>* popIndex(int i, bool cleanup = true) {
		Node<T>* iter = head;
		if (size > 0) {
			if (i == 0) popHead();
			else if (i == size - 1) popTail();
			else if (i > 0 && i < size - 1) {
				while (i > 0) {
					iter = iter->next;
					i--;
				}
				iter->prev->next = iter->next;
				iter->next->prev = iter->prev;
				size--;
				if (cleanup) {
					delete n;
					return NULL;
				}
				else {
					iter->prev = NULL;
					iter->next = NULL;
					return iter;
				}
			}
		}
		else return NULL;
	}

	Node<T>* popNode(Node<T>* n, bool cleanup = true) {
		if (contains(n)) {
			if (n->next != NULL) n->next->prev = n->prev;
			else head = n->next;
			if (n->prev != NULL) n->prev->next = n->next;
			else tail = n->prev;
			size--;
			if (cleanup) {
				delete n;
				return NULL;
			}
			else {
				n->prev = NULL;
				n->next = NULL;
				return n;
			}
		}
		else return NULL;
	}

	Node<T>* getNodeAt(int i) {
		if (i >= 0 && i < size) {
			if (i == 0) return head;
			else if (i == size - 1) return tail;
			else {
				Node<T>* iter = head;
				while (i > 0) {
					iter = iter->next;
					i--;
				}
				return iter;
			}
		}
		else return NULL;
	}

	bool contains(Node<T>* n) {
		Node<T>* iter = head;
		while (iter != NULL) {
			if (iter == n) return true;
			else iter = iter->next;
		}
		return false;
	}

	int getIndex(Node<T>* n) {
		int i = 0;
		Node<T> iter = head;
		while (iter != NULL) {
			if (iter == n) return i;
			else { i++; iter = iter->next; }
		}
		return -1;
	}

	int getSize() { return size; }

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

	void clearList() {
		Node<T>* iter = head;
		while (iter != NULL) {
			Node<T>* tmp = iter;
			iter = iter->next;
			delete tmp;
		}
		head = NULL;
		tail = NULL;
		size = 0;
	}

	~LinkedList() { clearList(); }
};
