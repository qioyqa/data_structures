#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T> *next;

    Node(T data = T(), Node<T> *next = nullptr): data(data), next(next){};
};

template <typename T>
class Queue{
private:
    int ssize;
    Node<T> *head;
public:
    friend ostream& operator<<(ostream& os, const Queue<T>& queue){
        Node<T>* curr = queue.head;
        while(curr != nullptr){
            os<< curr->data;
            if(curr->next != nullptr){
                os << "->";
            }
            curr = curr->next;
        }
        os << "->" << endl;
        return os;
    }

    Queue();
    ~Queue();

    void enqueue(T data);
    T dequeue();
    T front();
    bool isEmpty();
    int size(){return ssize;};
    void pop();
    void clear();
};

template <typename T>
Queue<T>::Queue(){
    ssize = 0;
    head = nullptr;
}

template <typename T>
Queue<T>::~Queue(){
    clear();
}

template <typename T>
void Queue<T>::enqueue(T data) {
    Node<T> *nNode = new Node<T>(data); 
    if(head == nullptr){
        head = nNode;
    }else{
        nNode->next = head;
        head = nNode;
    }
    ssize++;
}

template <typename T>
T Queue<T>::dequeue(){
    Node<T> *toDelete = new Node<T>;
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return T();
    }else{
        T val{};
        Node<T> *prev = head;
        for(int i{}; i < ssize-2; i++){
            prev = prev->next;
        }
        toDelete = prev->next;
        val = toDelete->data;
        delete toDelete;
        ssize--;
        prev->next = nullptr;
        return val;
    }
}

template <typename T>
T Queue<T>::front(){
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return T();
    }
    return head->data;
}

template <typename T>
bool Queue<T>::isEmpty(){
    return (ssize == 0) ? true : false;
}

template <typename T>
void Queue<T>::pop(){
    Node<T> *toDelete = new Node<T>;
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return;
    }else{
       toDelete = head;
       head = toDelete->next;
       delete toDelete;
       ssize--;
       return;       
    }
}
template <typename T>
void Queue<T>::clear() {
    while(head != nullptr){
        pop();
    }
};
