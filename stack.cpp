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
public:
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

    int get_size();
    void push(T data);
    T pop();
    T top();
    void clear();
    bool empty();
    
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
int stack<T>::get_size()
{
    return size;
}

template <typename T>
void stack<T>::push(T data)
{
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
T stack<T>::top(){
    return head->data;
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

template <typename T>
bool stack<T>::empty(){
    return (size == 0) ? true : false;
}
