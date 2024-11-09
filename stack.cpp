#include <iostream>
using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T> *next;
    Node(T data = T(), Node<T> *next = nullptr);
};

template <typename T>
class stack{
private:
    Node<T>* head;
    int size;
public:
    stack();
    ~stack();

    friend ostream& operator<<(ostream& os, const stack<T>& stack){
        Node<T>* curr = stack.head;
        while(curr != nullptr){
            os<< curr->data;
            if(curr->next != nullptr){
                os << "->";
            }
            curr = curr->next;
        }
        os << "|" << endl;
        return os;
    }

    void push(T data);
    T pop();
    void clear();
};

template <typename T>
Node<T>::Node(T data, Node<T> *next){
    this->data = data;
    this->next = next;
}

template <typename T>
stack<T>::stack(){
    size = 0;
    head = nullptr;
}

template <typename T>
stack<T>::~stack(){
    clear();
}

template <typename T>
void stack<T>::push(T data){
    Node<T> *nNode = new Node<T>(data);
    if(!head){
        head = nNode;
    }else{
        nNode->next = head;
        head = nNode;
    }
    size++;
}

template <typename T>
T stack<T>::pop(){
    Node<T> *toDelete = head;
    if(!head){
        return T();
    }else{
        head = head->next;
        T val = toDelete->data;
        delete toDelete;
        size--;
        return val;
    }
    
}

template <typename T>
void stack<T>::clear(){
    if(!head){
        return;
    }else{
        while(head != nullptr){
            Node<T> *toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }
    size = 0;
}