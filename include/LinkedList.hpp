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
    void pushHead(T val); // inserts data at the beginning/end of the list
    void pushTail(T val);
    node<T>* popHead(); // removes first/last node from list and returns a pointer to it
    node<T>* popTail(); // (if the pointer is unused then use the delete function in conjunction with popHead/Tail)
    void remove(node<T>* n);
    void remove(T n);
    void reverse(); // inverts the order of the nodes
    T& operator[](int index); // overloads the array index operator "[]"
    void printList(); // prints a list of ints

    int getSize();
    void randGenInt(int length, int lowBound, int upBound); //generates a random list of ints
};