#pragma once
#include <cstddef>
//#include "LinkedList.hpp"

template<class S>
struct node {
    S data;
    node<S>* prev;
    node<S>* next;
};

template<class T>
class LinkedList {
protected:
    node<T>* head;
    node<T>* tail;
    int size;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    LinkedList(int length, bool randomizeData = false) {
        head = NULL;
        tail = NULL;
        size = length;
        while (length > 0) {
            pushTail(randomizeData ? /* random function to be implemented */ : NULL);
            length--;
        }
    }

    void pushHead(T val) {
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

    void pushTail(T val) {
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

    node<T>* popHead() {
        node<T>* temp = head;
        if (size == 1) {
            size--;
            head = NULL;
            tail = NULL;
        } else if (size > 1) {
            size--;
            head = head->next;
            head->prev = NULL;
        }
        return temp;
    }

    node<T>* popTail() {
        node<T>* temp = tail;
        if (size == 1) {
            size--;
            head = NULL;
            tail = NULL;
        } else if (size > 1) {
            size--;
            tail = tail->prev;
            tail->next = NULL;
        }
        return temp;
    }

    void remove(node<T>* n) {
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

    void remove(T val) {
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

    void reverse() {
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

    T& operator[](int index) {
        node<T>* iter;
        if (index+1 <= size/2) {
            iter = head;
            int i = 0;
            while (i < index) {
                iter = iter->next;
                i++;
            }
        } else {
            iter = tail;
            int i = size-1;
            while (i > index) {
                iter = iter->prev;
                i--;
            }
        }
        return iter->data;
    }

    char* toString() {
        //work in progress
        return NULL;
    }
};