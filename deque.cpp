#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;
    Node(T data = T(), Node<T> *prev = nullptr, Node<T> *next = nullptr) 
        : data(data), prev(prev), next(next) {};
};

template <typename T>
class Dequeue {
private:
    void cout_empty() { cout << "deque is empty" << endl; };
    int ssize;
    Node<T> *head;
    Node<T> *tail;

public:
    friend ostream &operator<<(ostream &os, const Dequeue<T> &deque) {
        Node<T> *curr = deque.head;
        os << "<->";
        while (curr != nullptr) {
            os << curr->data;
            if (curr->next != nullptr) {
                os << "->";
            }
            curr = curr->next;
        }
        os << "<->" << endl;
        return os;
    }

    Dequeue() : ssize(0), head(nullptr), tail(nullptr) {};
    ~Dequeue() {
        clear();
    };

    void push_back(T data);
    void push_front(T data);
    T pop_back();
    T pop_front();
    T front();
    T back();
    bool isEmpty();
    int size();
    void clear();
};

template <typename T>
void Dequeue<T>::push_back(T data) {
    Node<T> *nNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = nNode;
    } else {
        tail->next = nNode;
        nNode->prev = tail;
        tail = nNode;
    }
    ssize++;
}

template <typename T>
void Dequeue<T>::push_front(T data) {
    Node<T> *nNode = new Node<T>(data, nullptr, head);
    if (isEmpty()) {
        head = tail = nNode;
    } else {
        head->prev = nNode;
        head = nNode;
    }
    ssize++;
}

template <typename T>
T Dequeue<T>::pop_back() {
    if (isEmpty()) {
        cout_empty();
        return T();
    }
    T val = tail->data;
    Node<T> *toDelete = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete toDelete;
    ssize--;
    return val;
}

template <typename T>
T Dequeue<T>::pop_front() {
    if (isEmpty()) {
        cout_empty();
        return T();
    }
    T val = head->data;
    Node<T> *toDelete = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete toDelete;
    ssize--;
    return val;
}

template <typename T>
T Dequeue<T>::front() {
    if (isEmpty()) {
        cout_empty();
        return T();
    }
    return head->data;
}

template <typename T>
T Dequeue<T>::back() {
    if (isEmpty()) {
        cout_empty();
        return T();
    }
    return tail->data;
}

template <typename T>
bool Dequeue<T>::isEmpty() {
    return ssize == 0;
}

template <typename T>
int Dequeue<T>::size() {
    return ssize;
}

template <typename T>
void Dequeue<T>::clear() {
    while (!isEmpty()) {
        pop_front();
    }
}
