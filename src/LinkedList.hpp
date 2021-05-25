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
    LinkedList();
    void pushHead(T val);   //inserts data at the beginning/end of the list
    void pushTail(T val);
    T popHead();    //deletes first/last node and returns its data
    T popTail();
    void remove(node<T>* n);
    void remove(T n);
    void reverse();     //inverts the order of the nodes
    T& operator[](int index);   //overloads the array index operator "[]"
    void printList();   //prints a list of ints
    int getSize();
    void randGenInt(int length, int lowBound, int upBound); //generates a random list of ints
};