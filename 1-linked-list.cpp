#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class List {
public:
    friend ostream& operator<<(ostream& os, const List<T>& list) {
        typename List<T>::Node<T>* curr = list.head;
        while (curr != nullptr) {
            os << "[" << curr->data << "]";
            if (curr->pNext != nullptr) {
                os << "->";
            }
            curr = curr->pNext;
        }
        os << "->nullptr" << endl;
        return os;
    }

    List();        
    List(initializer_list<T> initList);
    ~List();


    void push_back(T data);
    void push_front(T data);
    void insert(T data, int index);
    void remove(int index);
    void pop_front();
    void pop_back();
    void clear();

    T& operator[](const int idx);
    int size() const { return size_; }

private:
    template<typename T1>
    class Node {
    public:
        Node* pNext;
        T data;
        Node(T1 data = T1(), Node* pNext = nullptr) : data(data), pNext(pNext) {}
    };

    int size_; 
    Node<T>* head; 
};


template <typename T>
List<T>::List() : size_(0), head(nullptr) {}

template <typename T>
List<T>::List(initializer_list<T> initList) : size_(0), head(nullptr) {
    for (const T& val : initList) {
        push_back(val);
    }
}


template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::push_back(T data) {
    Node<T>* newNode = new Node<T>(data);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* curr = head;
        while (curr->pNext != nullptr) {
            curr = curr->pNext;
        }
        curr->pNext = newNode; 
    }
    size_++;
}

template <typename T>
void List<T>::push_front(T data) {
    head = new Node<T>(data, head);
    size_++;
}

template <typename T>
void List<T>::insert(T data, int index) {
    if (index == 0) {
        push_front(data);
        return;
    }

    if (index < 0 || index >= size_) {
        throw out_of_range("Index out of range");
    }

    Node<T>* prev = head;
    for (int i = 0; i < index - 1; ++i) {
        prev = prev->pNext;
    }

    Node<T>* newNode = new Node<T>(data, prev->pNext);
    prev->pNext = newNode;
    size_++;
}


template <typename T>
void List<T>::remove(int index) {
    if (index == 0) {
        pop_front();  
        return;
    }

    if (index < 0 || index >= size_) {
        throw out_of_range("Index out of range");
    }

    Node<T>* prev = head;
    for (int i = 0; i < index - 1; ++i) {
        prev = prev->pNext; 
    }

    Node<T>* toDelete = prev->pNext;  
    prev->pNext = toDelete->pNext;  
    delete toDelete;  
    size_--;
}


template <typename T>
void List<T>::pop_front() {
    if (head == nullptr) return;  

    Node<T>* toDelete = head;
    head = head->pNext; 
    delete toDelete; 
    size_--;
}

template <typename T>
void List<T>::pop_back() {
    if (head == nullptr) return;
    remove(size_ - 1); 
}

template <typename T>
void List<T>::clear() {
    while (head != nullptr) {
        pop_front(); 
    }
}


template <typename T>
T& List<T>::operator[](const int idx) {
    if (idx < 0 || idx >= size_) {
        throw out_of_range("Index out of range");
    }

    Node<T>* curr = head;
    for (int i = 0; i < idx; ++i) {
        curr = curr->pNext;
    }
    return curr->data;
}

