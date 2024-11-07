#include <initializer_list>
using namespace std;

template <typename T>
class List{
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

        int getSize(){return size;}

        T& operator[](const int idx);

        void pop_front();

        void clear();

        void push_front(T data);

        void insert(T data, int index);

        void remove(int index);

        void pop_back();
private:
    template<typename T1>
    class Node{

    public:
        Node *pNext;
        T data;
        Node(T1 data=T1(), Node* pNext=nullptr){

            this->data = data;
            this->pNext = pNext;
        }
    };

    int size;
    Node<T> *head;
};

template <typename T>
List<T>::List(){
    size = 0;
    head = nullptr;
}

template <typename T>
List<T>::List(initializer_list<T> initList){
    size = 0;
    head = nullptr;
    for (const T& val : initList){
        push_back(val);
    }
}

template <typename T>
List<T>::~List(){
    clear();
}

template <typename T>
void List<T>::push_back(T data){
    if(head == nullptr){
        head = new Node<T>(data);
    }else{
        Node<T> *curr = this->head;
        while (curr-> pNext != nullptr)
        {
            curr = curr->pNext;
        }
        curr->pNext = new Node<T>(data);
    }

    size++;
}

template <typename T>
T &List<T>::operator[](const int idx)
{
    int counter = 0;
    Node<T> *curr = this->head;

    while (curr != nullptr){
        if(counter == idx){
            return curr->data;
        }

        curr = curr->pNext;
        counter++;
    }
}

template <typename T>
void List<T>::pop_front(){
    Node<T> *curr = this->head;

    head = head->pNext;

    delete curr;

    size--;
}

template <typename T>
void List<T>::clear()

{;
    Node<T> *curr = this->head;
    while (curr != nullptr){
        Node<T> *curr = head;
        if(head != nullptr){
            head= head->pNext;
            delete curr;
            size--;
        }else{
            break;
        }
    }
}

template <typename T>
void List<T>::push_front(T data){
    head = new Node<T>(data, head);
    size++;
}

template <typename T>
void List<T>::insert(T data, int index){
    if(index == 0) push_front(data);
    Node<T> *prev = this->head;

    for(int i{0}; i < (index - 1); i++){
        prev = prev->pNext;
    }
    Node<T> *nNode = new Node(data, prev->pNext);
    prev->pNext = nNode;
    size++;
}

template <typename T>
void List<T>::remove(int index){
    if(index == 0) pop_front();

    Node<T> *prev = this-> head;

    for(int i{}; i < index - 1; ++i){
        prev = prev->pNext;
    }

    Node<T> *to_delete = prev->pNext;

    prev->pNext = to_delete->pNext;

    delete to_delete;
    
    size--;
}

template <typename T>
void List<T>::pop_back()
{
    remove(size-1);
}
