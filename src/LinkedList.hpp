/*
template<class T>
struct node {
    T data;
    node<T>* prev;
    node<T>* next;
};

template<class T>
class LinkedList {
protected:
    node<T>* head, tail;
    int size;
public:
    LinkedList();
    LinkedList(int length, bool randomizeData);
    void pushHead(T val); // inserts data at the beginning/end of the list
    void pushTail(T val);
    T* popHead(); // removes first/last node from list and returns a pointer to it
    T* popTail(); // (if the pointer is unused then use the delete function in conjunction with popHead/Tail)
    void remove(node<T>* n);
    void remove(T n);
    void reverse(); // inverts the order of the nodes
    T& operator[](int index); // overloads the array index operator "[]"
    char* toString(); // currently empty
};
*/